#pragma once
#include "elements.h"
#include "renderer.h"
#include "../map/map.h"
#include <functional>

class GameWindow {
	public:

		GameWindow();
        void startGameLoop(const std::function<void(SDL::Event&)>& eventLogic, const std::function<void()>& loopLogic, const Map& map);
		void startRenderLoop(const Map& map);

	private:

		Smart::Window window{ nullptr };
		Renderer renderer{};

		void initializeLibraries();
        void allocateUIResources();

		void renderMap(const Map& map);
		void addStatusToRenderer(const Map& map);
		void addMapToRenderer(const Map& map);
		void addTileToRenderer(char tile);
		void addPlayerToRenderer(const Map& map);

};
