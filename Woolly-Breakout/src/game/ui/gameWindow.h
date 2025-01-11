#pragma once
#include "elements.h"
#include "renderer.h"
#include "../map/map.h"
#include "../entities/player.h"
#include <functional>

class GameWindow {
	public:

		GameWindow(bool isMultiplayer = false, bool isFirstPlayers = true);
        void startGameLoop(const std::function<void(SDL::Event&)>& eventLogic, const std::function<void()>& loopLogic, const Map& map);
		void startRenderLoop(const Map& map);

	private:

		Smart::Window window{ nullptr };
		Renderer renderer{};
		bool isMultiplayerGame{ false };
		bool isFirstPlayerPerspective{ true };

		void initializeLibraries();
        void allocateUIResources();

		void renderMap(const Map& map);
		void addStatusToRenderer(const Map& map);
		void addMapToRenderer(const Map& map);
		void addTileToRenderer(char tile);
		void addPlayersToRenderer(const Map& map);		
};
