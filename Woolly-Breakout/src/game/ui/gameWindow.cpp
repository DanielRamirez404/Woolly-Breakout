#include "gameWindow.h"
#include "elements.h"
#include "../../constants/constants.h"
#include "../map/utilities.h"
#include "../entities/safe-zone.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdexcept>
#include <functional>
#include <string_view>

GameWindow::GameWindow() {
	initializeLibraries();
    allocateUIResources();
}

void GameWindow::startGameLoop(const std::function<void(SDL::Event&)>& eventLogic, const std::function<void()>& loopLogic, const Map& map) {
    SDL::Event event{};
    constexpr int delayTime{ 1000 / Constants::fps };
		
	renderMap(map);

    while (true) {

		loopLogic();
        
        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT)
				return;

            eventLogic(event);
        }

		SDL_Delay(delayTime);
		renderMap(map);
    }
}

void GameWindow::initializeLibraries() {
	
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL Initialization Error");

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw std::runtime_error("SDL_Image Initialization Error");	
}

void GameWindow::allocateUIResources() {
    window.reset(SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Constants::windowSize, Constants::windowSize, SDL_WINDOW_SHOWN));

	if (!window)
		throw std::runtime_error("Window Initialization Error");
	
	renderer.setRenderer(window.get());
	
	if (!renderer)
		throw std::runtime_error("Renderer Initialization Error");   

    renderer.setTransparentMode();

	constexpr std::string_view names[] { "grass", "wall", "player", "key", "door", "frame" };

	for (std::string_view name : names)
		renderer.loadTexture(name.data());
}

void GameWindow::renderMap(const Map& map) {
	renderer.clear();

	addMapToRenderer(map);
	addPlayerToRenderer(map);
	addStatusToRenderer(map);

	renderer.render();
}

void GameWindow::addStatusToRenderer(const Map& map) {
	renderer.setArea(0, 0, Constants::windowSize, Constants::statusBarLength);
	renderer.addColor(0, 0, 0, 255);

	int pickedKeys{ map.getPickedUpKeys() };

	for (int i{0}; i < 3; ++i) {

		renderer.setArea(Constants::framePadding + Constants::frameSize * i, Constants::framePadding, Constants::frameSize);
		renderer.addTexture("frame");
		
		if (i < pickedKeys)
			renderer.addTexture("key");
	}
}

void GameWindow::addMapToRenderer(const Map& map) {

	const Coordinates<float>& player{ map.getPlayerCoordinates() };

	constexpr int tilesToCenter{ Constants::middleRenderedTile - 1 };

	const int min_i{ static_cast<int>(player.i) - tilesToCenter };
	const int max_i{ static_cast<int>(player.i) + tilesToCenter };
	const int min_j{ static_cast<int>(player.j) - tilesToCenter };
	const int max_j{ static_cast<int>(player.j) + tilesToCenter };

	auto increase_i{ [&](int& i, int&i_count) {  
		++i;
		++i_count;
	}};

	auto increase_j{ [&](int& j, int&j_count) {  
		++j;
		++j_count;
	}};

	for (int i{min_i}, i_count{0}; i <= max_i; increase_i(i, i_count))
		for (int j{min_j}, j_count{0}; j <= max_j; increase_j(j, j_count)) {

			char tile{};

			if (i < 0 || j < 0 || i > Constants::mapSize || j > Constants::mapSize)
				continue;

			tile = map.getMatrix()[i][j];			

			renderer.setArea(j_count * Constants::tileSize, i_count * Constants::tileSize, Constants::tileSize);

			switch (tile) {
				case '0':
					renderer.addTexture("grass");
					break;
				case '1':
					renderer.addTexture("wall");
					break;
				case '2':
					renderer.addTexture("grass");
					if (!map.isSafeZoneOpen())
						renderer.addTexture("door");
					break;
				case '3':
					renderer.addTexture("grass");
					renderer.addTexture("key");
				default:
					break;
			} 				
		}
}

void GameWindow::addPlayerToRenderer(const Map& map) {
	const Coordinates<float>& player{ map.getPlayerCoordinates() };
	renderer.setArea(Constants::playersTileStart, Constants::playersTileStart, Constants::tileSize);
	renderer.addTexture("player");
}