#include "game.h"
#include "map/map.h"
#include "ui/elements.h"
#include "entities/player.h"
#include "map/utilities.h"
#include "../constants/notation.h"
#include "../constants/constants.h"
#include "../networking/classes/host.h"
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

Game::Game() : Game::Game("") {};

void Game::run() {
	switch (hostType) {
		case Host::None:
			map.emplace();
			startGame();
			break;
		
		case Host::Server:
			map.emplace(false);
			tryNetworkingFunction(std::bind(&Game::hostGame, this));
			break;

		case Host::Client:
			map.emplace(false);
			tryNetworkingFunction(std::bind(&Game::joinGame, this));
			break;
	}
}

void Game::startGame(bool isMultiplayer, bool isFirstPlayers) {
	GameWindow gameWindow{ isMultiplayer, isFirstPlayers };
	gameWindow.startGameLoop(
		map.value(), 
		[&](SDL::Event& event) { handleInput(getThisPlayer(), event); }, 
		[&]() { map.value().handlePlayerInteractions(getThisPlayer(), [&]() { isRunning = false; }); },
		[&]() { 
			if (hostType == Host::None)
				isRunning = false;
			else
				map.value().addEvent({ Map::Event::Quit, "Oops!" }); 
		},
		[&]() { return !isRunning; }
	);
}

void Game::hostGame() {
	GameServer server{Constants::Networking::defaultPort};
	server.getAcceptingThread().join();
	server.broadcast( std::string{'m', 1}.append(map.value().toString()) );

	runMultiplayerThreads(server);
}

void Game::joinGame() {
	GameClient client{};
	client.connectTo(server_IPv4.value(), Constants::Networking::defaultPort);

	runMultiplayerThreads(client);
}

void Game::runMultiplayerThreads(GameHost& host) {
	auto threads{
		host.getMessageThreads(
			[&](std::string message) { handleMessageReading(getTeammate(), message); },
			[&]() { return getNetworkingMessage(getThisPlayer()); },
			[&]() { return isRunning; }
		)
	};

	std::thread game{ [&]() { startGame(true, hostType == Host::Server); }};
	threads.second.join();
	threads.first.join();
	game.join();
}

std::string Game::getNetworkingMessage(Player& player) {
	constexpr int eventSendingTimes{ 5 };
	static int eventSentCount{ 5 }; 		// initialized as if an event were already sent
	static std::string eventMessage{ "" };

	if (!map.value().isThereAnyEvent() && eventSentCount >= eventSendingTimes) {
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(5us);
		return std::string{'p', 1}.append(player.getCoordinates().toString());
	}

	if (eventSentCount < eventSendingTimes)
		++eventSentCount;
	else {
		eventSentCount = 0;
		auto event{ map.value().getFirstEvent() };

		switch (event.first) {
			case Map::Event::PickUpKey:
				eventMessage = std::string{'k', 1}.append(event.second); 
				break;
			case Map::Event::Win:
				isRunning = false;
				eventMessage = std::string{'w', 1};
				break;
			case Map::Event::Quit:
				isRunning = false;
				eventMessage = std::string{'q', 1};
		}
	}

 	return eventMessage;	
}

void Game::handleMessageReading(Player& player, std::string& message) {
	char startingFlag{ message[0] };
	std::string info{ message.substr(2) };

	if (startingFlag == 'p')
		player.getCoordinates().read(info);
	else if (startingFlag == 'k')
		map.value().handlePickingKeyUp(info);
	else if (startingFlag == 'm')
		map.value().readString(info);
	else if (startingFlag == 'w' || startingFlag == 'q')
		isRunning = false;
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

Player& Game::getThisPlayer() {
	return (hostType == Host::Client) ? map.value().getSecondPlayer() : map.value().getPlayer();
}

Player& Game::getTeammate() {
	return (hostType != Host::Client) ? map.value().getSecondPlayer() : map.value().getPlayer();
}
