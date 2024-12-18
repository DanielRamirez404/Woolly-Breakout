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

	renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));

	if (!renderer)
		throw std::runtime_error("Renderer Initialization Error");   

    allocateImages();
}

void GameWindow::allocateImages() {
	SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);

	std::array<std::string, 6> names = { 
		{ "grass", "wall", "player", "key", "door", "frame" } 
	};

	for (const std::string& name : names)
		textures.emplace(name, loadImage("../../res/" + name + ".png"));
}

SDL::Texture* GameWindow::loadImage(std::string_view path) {
	
    Smart::Surface temp;
	temp.reset( IMG_Load(path.data()) );

	if (!temp)
		throw std::runtime_error(std::string("Can\'t load image from path: ") + std::string(path));

	SDL::Texture* texture{ SDL_CreateTextureFromSurface(renderer.get(), temp.get()) };

	if (!texture)
		throw std::runtime_error(std::string("Can\'t create image texture from path: ") + std::string(path));

	return texture;
}

void GameWindow::renderMap(const Map& map) {

	SDL_RenderClear(renderer.get());

	const Map::Matrix& matrix = map.getMatrix();

	for (int i{0}; i < Constants::mapSize; ++i)
		for (int j{0}; j < Constants::mapSize; ++j) {

			SDL_Rect square{ j * Constants::tileWidth, Constants::statusBarLength + (i * Constants::tileLength), Constants::tileWidth, Constants::tileLength };
			
			const char& tile{ matrix[i][j] }; 

			auto& texture = (tile == '1') ? textures["wall"] : textures["grass"];
			SDL_RenderCopy(renderer.get(), texture.get(), nullptr, &square);
		}

	const SafeZone& safeZone{ map.getSafeZone() };
	const Coordinates<int>& door{ safeZone.getDoor() };
	auto& doorTexture{ safeZone.isOpen() ? textures["grass"] : textures["door"] };

	SDL_Rect doorTile{ door.j  * Constants::tileWidth, Constants::statusBarLength + door.i * Constants::tileLength, Constants::tileWidth, Constants::tileLength };
	SDL_RenderCopy(renderer.get(), doorTexture.get(), nullptr, &doorTile);

	for (const auto& key : safeZone.getKeys()) {
		SDL_Rect tile{ key.j * Constants::tileWidth, Constants::statusBarLength + key.i * Constants::tileLength, Constants::tileWidth, Constants::tileLength };
		SDL_RenderCopy(renderer.get(), textures["key"].get(), nullptr, &tile);
	}

	const Coordinates<float>& player{ map.getPlayer() };

	SDL_Rect tile{ static_cast<int>(player.j * Constants::tileWidth), Constants::statusBarLength + static_cast<int>(player.i * Constants::tileLength), Constants::tileWidth, Constants::tileLength };
	SDL_RenderCopy(renderer.get(), textures["player"].get(), nullptr, &tile);

	SDL_Rect statusRect{ 0, 0, Constants::windowSize, Constants::statusBarLength};
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
	SDL_RenderFillRect(renderer.get(), &statusRect);

	int pickedKeys{ safeZone.getPickedUpKeys() };

	for (int i{0}; i < 3; ++i) {
		SDL_Rect frame{ Constants::framePadding + Constants::frameSize * i, Constants::framePadding, Constants::frameSize, Constants::frameSize};
		SDL_RenderCopy(renderer.get(), textures["frame"].get(), nullptr, &frame);
		if (i < pickedKeys)
			SDL_RenderCopy(renderer.get(), textures["key"].get(), nullptr, &frame);
	}

	SDL_RenderPresent(renderer.get());
}
