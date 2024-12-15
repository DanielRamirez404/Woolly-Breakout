#include "gameWindow.h"
#include "constants.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdexcept>
#include <memory>
#include <functional>
#include <string>
#include <string_view>

GameWindow::GameWindow() {
	initializeLibraries();
    allocateUIResources();
}

void GameWindow::startGameLoop(const std::function<void(SDL_Event&)>& eventLogic, const Map& map) {
    SDL_Event event{};
	constexpr int fps{ 24 };
    constexpr int delayTime{ 1000 / fps };
		
	renderMap(map);

    while (true) {
        
        while (SDL_WaitEvent(&event)) {

            if (event.type == SDL_QUIT)
				return;

            eventLogic(event);

            SDL_Delay(delayTime);
            renderMap(map);
        }
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
	
    grassTexture.reset(loadImage("../../res/grass.png"));
	wallTexture.reset(loadImage("../../res/wall.png"));
	playerTextre.reset(loadImage("../../res/player.png"));
}

SDL_Texture* GameWindow::loadImage(std::string_view path) {
	
    std::unique_ptr<SDL_Surface, GameWindow::deleter> temp;
	temp.reset( IMG_Load(path.data()) );

	if (!temp)
		throw std::runtime_error(std::string("Can\'t load image from path: ") + std::string(path));

	SDL_Texture* texture{ SDL_CreateTextureFromSurface(renderer.get(), temp.get()) };

	if (!texture)
		throw std::runtime_error(std::string("Can\'t create image texture from path: ") + std::string(path));

	return texture;
}

void GameWindow::renderMap(const Map& map) {

	SDL_RenderClear(renderer.get());
	SDL_SetRenderDrawColor(renderer.get(), 0, 255, 255, 150);

	SDL_Rect squareRect{ 0, 0, Constants::windowSize, Constants::windowSize };

	const Map::Matrix& matrix = map.getMatrix();

	for (int i{0}; i < Constants::mapSize; ++i)
		for (int j{0}; j < Constants::mapSize; ++j) {
			SDL_Rect tile{ j * Constants::tileSize, i * Constants::tileSize, Constants::tileSize, Constants::tileSize };
			auto& texture = (matrix[i][j] == '1') ? wallTexture : grassTexture;
				SDL_RenderCopy(renderer.get(), texture.get(), nullptr, &tile);
		}

	const Map::Coordinates& player = map.getPlayer();

	SDL_Rect tile{ player.j * Constants::tileSize, player.i * Constants::tileSize, Constants::tileSize, Constants::tileSize };
	SDL_RenderCopy(renderer.get(), playerTextre.get(), nullptr, &tile);

	SDL_RenderPresent(renderer.get());
}
