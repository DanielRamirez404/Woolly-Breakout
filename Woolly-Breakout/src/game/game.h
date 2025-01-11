#pragma once
#include "map/map.h"
#include "ui/gameWindow.h"
#include "SDL.h"
#include <string>
#include <optional>
#include <unordered_map>

class Game {
	public:

		Game(std::string prompt);

		enum Host {
			Server,
			Client,
			None,
		};

		void run();

	private:

		Host hostType{};
		std::optional<std::string> server_IPv4{};
		std::optional<std::string> queuedMessage{};
		std::optional<Map> map{ std::nullopt };

		void startSoloGame();
		void hostGame();
		void joinGame();

		void handleSoloInput(SDL_Event& event);
		void handleMultiplayerInput(SDL_Event& event);
		void handleLogic();
};
