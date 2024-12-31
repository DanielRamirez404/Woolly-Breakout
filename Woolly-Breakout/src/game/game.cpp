#include "game.h"
#include "map/map.h"
#include "entities/player.h"
#include "map/utilities.h"
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
	GameWindow gameWindow{};
	gameWindow.startGameLoop(std::bind(&Game::handleEvents, this, std::placeholders::_1), std::bind(&Game::handleLogic, this), map);
}

void Game::hostGame() {
	tryNetworkingFunction([&]() {

        GameServer server{Constants::Networking::defaultPort};
        server.getAcceptingThread().join();

        auto threads{
            server.getMessageThreads(
                [](std::string message) {
                    std::cout << message;
                },

                [&]() {
                    return std::optional<std::string>{ map.toString() };
                },

                []() { return true; }
            )
        };

		std::thread{ [&]() {
			GameWindow gameWindow{};
			gameWindow.startGameLoop(std::bind(&Game::handleEvents, this, std::placeholders::_1), std::bind(&Game::handleLogic, this), map); 
		}}.join();

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
					map.readString(std::move(message));
                },

                []() {
                    static int count{0};
                    ++count;

                    if (count <= 3)
                        return std::optional<std::string>{"hello, server!\n"};
                    
                    return std::optional<std::string>{std::nullopt};
                },

                []() { return true; }
            )    
        };

		std::thread{ [&]() { 
			GameWindow gameWindow{};
			gameWindow.startRenderLoop(map); 
		} }.join();

        threads.first.join();
        threads.second.join();
	});
}

void Game::handleEvents(SDL_Event& event) {

	Player& player = map.getPlayer();

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
	map.handleInteractions();
}