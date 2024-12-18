#pragma once
#include "elements.h"
#include "../map/map.h"
#include <functional>
#include <string_view>
#include <string>
#include <unordered_map>

class GameWindow {
	public:

		GameWindow();
        void startGameLoop(const std::function<void(SDL::Event&)>& eventLogic, const std::function<void()>& loopLogic, const Map& map);

	private:

		Smart::Window window{ nullptr };
		Smart::Renderer renderer{ nullptr };
        std::unordered_map<std::string, Smart::Texture> textures{};

		void initializeLibraries();
        void allocateUIResources();
        void allocateImages();

		SDL::Texture* loadImage(std::string_view path);
		void renderMap(const Map& map);
};
