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
		std::bind(&Game::handleLocalInput, this, std::placeholders::_1),
		std::bind(&Game::handleLogic, this)
	);
}

void Game::hostGame() {

	map.emplace(false);

	tryNetworkingFunction([&]() {

        GameServer server{Constants::Networking::defaultPort};
        server.getAcceptingThread().join();
		server.broadcast( 
			std::string{
				1, 'm'
			}.append(map.value().toString())
		);

        auto threads{
            server.getMessageThreads(
                [&](std::string message) {
                    if (message == "W")
						map.value().getSecondPlayer().queueMove(Direction::UP);
					else if (message == "A")
						map.value().getSecondPlayer().queueMove(Direction::LEFT);
					else if (message == "S")
						map.value().getSecondPlayer().queueMove(Direction::DOWN);
					else if (message == "D")
						map.value().getSecondPlayer().queueMove(Direction::RIGHT);
                },

                [&]() {
					static bool sendFirstPlayer{ true };

					std::string message{};

					if (sendFirstPlayer)
						message.append("p").append(map.value().getPlayerString());
					else
						message.append("s").append(map.value().getSecondPlayerString());

					sendFirstPlayer ^= true;
				
					//somehow this helps to get a low latency, I believe... (I don't think it makes sense, though)
					std::cout << message << '\n';
					
                    return std::optional<std::string>{ message };
                },

                []() { return true; }
            )
        };

		std::thread{ [&]() {
			GameWindow gameWindow{true};
			gameWindow.startGameLoop(
				map.value(), 
				std::bind(&Game::handleLocalInput, this, std::placeholders::_1),
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
					char startingFlag{ message[1] };
					std::string info{ message.substr(2) };

					if (startingFlag == 'm')
						map.value().readString(info);
					else if (startingFlag == 'p')
						map.value().readPlayerString(info);
					else if (startingFlag == 's')
						map.value().readSecondPlayerString(info);
                },

                [&]() {
					auto message{ (quequedMessage) ? std::optional<std::string>{std::move(quequedMessage.value())} : std::optional<std::string>{ std::nullopt } };
					quequedMessage.reset();
					return message;
                },

                []() { return true; }
            )    
        };

		std::thread{ [&]() { 
			GameWindow gameWindow{true, false};
			gameWindow.startGameLoop(
				map.value(),
				std::bind(&Game::queueHostInput, this, std::placeholders::_1)
			); 
		} }.join();

        threads.first.join();
        threads.second.join();
	});
}

void Game::handleLocalInput(SDL_Event& event) {
	Player& player = map.value().getPlayer();

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

void Game::queueHostInput(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {

			case SDLK_w:
			case SDLK_UP:
				quequedMessage.emplace("W");
				break;

			case SDLK_a:
			case SDLK_LEFT:
				quequedMessage.emplace("A");
				break;

			case SDLK_s:
			case SDLK_DOWN:
				quequedMessage.emplace("S");
				break;

			case SDLK_d:
			case SDLK_RIGHT:
				quequedMessage.emplace("D");
				break;
		
			default:
				break;
		}
	}
}


void Game::handleLogic() {
	map.value().handleInteractions();
}