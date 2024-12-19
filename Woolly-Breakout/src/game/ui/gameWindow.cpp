#include "gameWindow.h"
#include "elements.h"
#include "../../constants/constants.h"
#include "../map/utilities.h"
#include "../entities/safe-zone.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdexcept>
#include <functional>
#include <string>
#include <array>
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

    allocateImages();
}

void GameWindow::allocateImages() {
	renderer.setTransparentMode();

	std::array<std::string, 6> names = { 
		{ "grass", "wall", "player", "key", "door", "frame" } 
	};

	for (std::string_view name : names)
		renderer.loadTexture(name.data());
}

void GameWindow::renderMap(const Map& map) {
	renderer.clear();

	const Map::Matrix& matrix = map.getMatrix();
	const SafeZone& safeZone{ map.getSafeZone() };
	const Coordinates<float>& player{ map.getPlayer() };

	for (int i{0}; i < Constants::mapSize; ++i)
		for (int j{0}; j < Constants::mapSize; ++j) {

			renderer.setArea(j * Constants::tileWidth, Constants::statusBarLength + i * Constants::tileLength, Constants::tileWidth, Constants::tileLength);

			switch (matrix[i][j]) {
				case '0':
					renderer.addTexture("grass");
					break;
				case '1':
					renderer.addTexture("wall");
					break;
				case '2':
					renderer.addTexture("grass");
					if (!safeZone.isOpen())
						renderer.addTexture("door");
					break;
				default:
					renderer.addTexture("grass");
					break;
			} 				
		}

	for (const auto& key : safeZone.getKeys()) {
		renderer.setArea(key.j * Constants::tileWidth, Constants::statusBarLength + key.i * Constants::tileLength, Constants::tileWidth, Constants::tileLength);
		renderer.addTexture("key");		
	}

	renderer.setArea(static_cast<int>(player.j * Constants::tileWidth), Constants::statusBarLength + static_cast<int>(player.i * Constants::tileLength), Constants::tileWidth, Constants::tileLength);
	renderer.addTexture("player");

	renderer.setArea(0, 0, Constants::windowSize, Constants::statusBarLength);
	renderer.addColor(0, 0, 0, 255);

	int pickedKeys{ safeZone.getPickedUpKeys() };

	for (int i{0}; i < 3; ++i) {

		renderer.setArea(Constants::framePadding + Constants::frameSize * i, Constants::framePadding, Constants::frameSize);
		renderer.addTexture("frame");
		
		if (i < pickedKeys)
			renderer.addTexture("key");
	}

	renderer.render();
}
