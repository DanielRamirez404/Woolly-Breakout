#include "game.h"
#include "map/map.h"
#include "ui/elements.h"
#include "entities/player.h"
#include "map/utilities.h"
#include "../constants/notation.h"
#include "../constants/constants.h"
#include "../networking/classes/server.h"
#include "../networking/classes/client.h"
#include "../networking/utilities.h"
#include <string>
#include <functional>
#include <optional>
#include <thread>
#include <utility>
#include <chrono>
#include <iostream>

Game::Game(std::string prompt) :
	hostType { (prompt == "") ? Host::None : ((prompt == "host") ? Host::Server : Host::Client) },
	server_IPv4{ (hostType == Host::Client) ? std::optional<std::string>{prompt} : std::optional<std::string>{std::nullopt} } {}

void Game::run() {
	switch (hostType) {
		case Host::None:
			map.emplace();
			startGame();
			break;
		
		case Host::Server:
			map.emplace(false);
			hostGame();
			break;

		case Host::Client:
			map.emplace(false);
			joinGame();
			break;
	}
}

void Game::startGame(bool isMultiplayer, bool isFirstPlayers) {
	GameWindow gameWindow{ isMultiplayer, isFirstPlayers };
	gameWindow.startGameLoop(
		map.value(), 
		[&](SDL::Event& event) { handleInput(getThisPlayer(), event); }, 
		[&]() { map.value().handlePlayerInteractions(getThisPlayer()); }
	);
}

void Game::hostGame() {

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
					else if (startingFlag == 'k')
						map.value().handlePickingKeyUp(info);
                },

                [&]() {
					if (map.value().isThereAnyEvent()) {
						auto event{ map.value().getFirstEvent() };
						switch (event.first) {
							case Map::Event::PickUpKey:
								return std::string{'k', 1}.append(event.second);
							case Map::Event::Win:
								return std::string{'w', 1};
						}	
					}

					using namespace std::chrono_literals;
					std::this_thread::sleep_for(5us);
					return std::string{'p', 1}.append(map.value().getPlayerString());
				},

                []() { return true; }
            )
        };

		std::thread{ [&]() { startGame(true); }}.join();
        threads.first.join();
        threads.second.join();
    });
}

void Game::joinGame() {

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
					else if (startingFlag == 'k')
						map.value().handlePickingKeyUp(info);
                },

                [&]() {
					if (map.value().isThereAnyEvent()) {
						auto event{ map.value().getFirstEvent() };
						switch (event.first) {
							case Map::Event::PickUpKey:
								return std::string{'k', 1}.append(event.second);
							case Map::Event::Win:
								return std::string{'w', 1};
						}	
					}

					using namespace std::chrono_literals;
					std::this_thread::sleep_for(5us);
					return std::string{'p', 1}.append(map.value().getSecondPlayerString());
                },

                []() { return true; }
            )    
        };

		std::thread{ [&]() { startGame(true, false); }}.join();
        threads.first.join();
        threads.second.join();
	});
}

Player& Game::getThisPlayer() {
	return (hostType == Host::Client) ? map.value().getSecondPlayer() : map.value().getPlayer();
}

void Game::handleInput(Player& player, SDL::Event& event) {
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