#pragma once
#include "elements.h"
#include "renderer.h"
#include "../map/map.h"
#include "../entities/player.h"
#include <functional>

class GameWindow {
	public:

		using EventHandler = std::function<void(SDL::Event&)>;
		using LogicHandler = std::function<void()>;
		using EndingHandler = std::function<bool()>;
		using QuittingHandler = std::function<void()>;

		GameWindow(bool isMultiplayer, bool isFirstPlayers);
        void startGameLoop(const Map& map, const EventHandler& onEvent, const LogicHandler& onLoop, const QuittingHandler& onQuit, const EndingHandler& endCondition);

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
