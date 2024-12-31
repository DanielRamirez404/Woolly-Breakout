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
		std::optional<std::string> server_IPv4;

		Map map{};

		void startSoloGame();
		void hostGame();
		void joinGame();

		void handleEvents(SDL_Event& event);
		void handleLogic();
};
