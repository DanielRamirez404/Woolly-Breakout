#include "game.h"
#include "map/map.h"
#include "entities/player.h"
#include "map/utilities.h"
#include "../constants/notation.h"
#include "../constants/constants.h"
#include "../networking/classes/server.h"
#include "../networking/classes/client.h"
#include "../networking/utilities.h"
#include "SDL.h"
#include <string>
#include <functional>
#include <optional>
#include <thread>
#include <utility>
#include <chrono>

Game::Game(std::string prompt) :
	hostType { (prompt == "") ? Host::None : ((prompt == "host") ? Host::Server : Host::Client) },
	server_IPv4{ (hostType == Host::Client) ? std::optional<std::string>{prompt} : std::optional<std::string>{std::nullopt} } {}

void Game::run() {
	switch (hostType) {
		case Host::None:
			startSoloGame();
			break;
		
		case Host::Server:
			hostGame();
			break;

		case Host::Client:
			joinGame();
			break;
	}
}

void Game::startSoloGame() {
	map.emplace();
	GameWindow gameWindow{};
	gameWindow.startGameLoop(
		map.value(), 
		std::bind(&Game::handleSoloInput, this, std::placeholders::_1),
		std::bind(&Game::handleLogic, this)
	);
}

void Game::hostGame() {

	map.emplace(false);

	tryNetworkingFunction([&]() {

        GameServer server{Constants::Networking::defaultPort};
        server.getAcceptingThread().join();
		server.broadcast( 
			std::string{'m', 1}.append(map.value().toString())
		);

        auto threads{
            server.getMessageThreads(
                [&](std::string message) {
                    char startingFlag{ message[0] };
					std::string info{ message.substr(2) };

					if (startingFlag == 'p')
						map.value().readSecondPlayerString(info);
                },

                [&]() {
					using namespace std::chrono_literals;
					std::this_thread::sleep_for(5us);

					return std::optional<std::string>{
						std::string{'p', 1}.append(map.value().getPlayerString())
					};
				},

                []() { return true; }
            )
        };

		std::thread{ [&]() {
			GameWindow gameWindow{true};
			gameWindow.startGameLoop(
				map.value(), 
				std::bind(&Game::handleMultiplayerInput, this, std::placeholders::_1),
				std::bind(&Game::handleLogic, this)
			); 
		}}.join();

        threads.first.join();
        threads.second.join();
    });
}

void Game::joinGame() {

	map.emplace(false);

	tryNetworkingFunction([&]() {
		GameClient client{};
        client.connectTo(server_IPv4.value(), Constants::Networking::defaultPort);
        
		auto threads { 
            client.getMessageThreads(
                [&](std::string message) {
					char startingFlag{ message[0] };
					std::string info{ message.substr(2) };

					if (startingFlag == 'p')
						map.value().readPlayerString(info);
					else if (startingFlag == 'm')
						map.value().readString(info);
                },

                [&]() {
					
					using namespace std::chrono_literals;
					std::this_thread::sleep_for(5us);

					return std::optional<std::string>{
						std::string{'p', 1}.append(map.value().getSecondPlayerString())
					};
                },

                []() { return true; }
            )    
        };

		std::thread{ [&]() { 
			GameWindow gameWindow{true, false};
			gameWindow.startGameLoop(
				map.value(),
				std::bind(&Game::handleMultiplayerInput, this, std::placeholders::_1),
				std::bind(&Game::handleLogic, this)
			); 
		} }.join();

        threads.first.join();
        threads.second.join();
	});
}

void Game::handleSoloInput(SDL_Event& event) {
	Player& player{ map.value().getPlayer() };

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
			case SDLK_w:
			case SDLK_UP:
				player.queueMove(Direction::UP);
				break;

			case SDLK_a:
			case SDLK_LEFT:
				player.queueMove(Direction::LEFT);
				break;

			case SDLK_s:
			case SDLK_DOWN:
				player.queueMove(Direction::DOWN);
				break;

			case SDLK_d:
			case SDLK_RIGHT:
				player.queueMove(Direction::RIGHT);
				break;
		
			default:
				break;
		}
	}
}

void Game::handleMultiplayerInput(SDL_Event& event) {
	Player& player{ (hostType == Host::Client) ? map.value().getSecondPlayer() : map.value().getPlayer() };

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
			case SDLK_w:
			case SDLK_UP:
				player.queueMove(Direction::UP);
				break;

			case SDLK_a:
			case SDLK_LEFT:
				player.queueMove(Direction::LEFT);
				break;

			case SDLK_s:
			case SDLK_DOWN:
				player.queueMove(Direction::DOWN);
				break;

			case SDLK_d:
			case SDLK_RIGHT:
				player.queueMove(Direction::RIGHT);
				break;
		
			default:
				break;
		}
	}
}

void Game::handleLogic() {
	Player& player{ (hostType == Host::Client) ? map.value().getSecondPlayer() : map.value().getPlayer() };
	map.value().handlePlayerInteractions(player);
}