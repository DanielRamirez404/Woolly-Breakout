#pragma once
#include "map/map.h"
#include "ui/gameWindow.h"
#include "SDL.h"

class Game {
	public:
			
		void run();

	private:

		GameWindow window{};
		Map map{};

		void handleEvents(SDL_Event& event);
		void handleLogic();
};
