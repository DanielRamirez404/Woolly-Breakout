#pragma once
#include "elements.h"
#include "renderer.h"
#include "../map/map.h"
#include <functional>

class GameWindow {
	public:

		GameWindow();
        void startGameLoop(const std::function<void(SDL::Event&)>& eventLogic, const std::function<void()>& loopLogic, const Map& map);

	private:

		Smart::Window window{ nullptr };
		Renderer renderer{};

		void initializeLibraries();
        void allocateUIResources();
        void allocateImages();

		void renderMap(const Map& map);
};
