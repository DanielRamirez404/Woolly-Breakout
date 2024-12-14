#include "game.h"
#include "map.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdexcept>
#include <memory>
#include <string>
#include <string_view>

Game::Game() {
	initializeLibraries();
}

void Game::initializeLibraries() {
		
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL Initialization Error");

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw std::runtime_error("SDL_Image Initialization Error");

	window.reset(SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_SHOWN));

	if (!window)
		throw std::runtime_error("Window Initialization Error");

	renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));

	if (!renderer)
		throw std::runtime_error("Renderer Initialization Error");

	loadResources();
}

void Game::run() {

	SDL_Event event{};
	constexpr int fps{ 24 };
		
	renderMap();

	while (true) {

		SDL_Delay(1000 / fps);

		while (SDL_WaitEvent(&event)) {

			if (event.type == SDL_QUIT)
				return;

			if (event.type == SDL_KEYDOWN) {
				
				switch (event.key.keysym.sym) {
				
					case SDLK_w:
					case SDLK_UP:
						map.movePlayer(Map::Direction::UP);
						break;

					case SDLK_a:
					case SDLK_LEFT:
						map.movePlayer(Map::Direction::LEFT);
						break;

					case SDLK_s:
					case SDLK_DOWN:
						map.movePlayer(Map::Direction::DOWN);
						break;

					case SDLK_d:
					case SDLK_RIGHT:
						map.movePlayer(Map::Direction::RIGHT);
						break;
				
					default:
						break;
				}
			}

			renderMap();
		}
	}
}

void Game::loadResources() {
	SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);	
	grassTexture.reset(loadImage("../../res/grass.png"));
	wallTexture.reset(loadImage("../../res/wall.png"));
	playerTextre.reset(loadImage("../../res/player.png"));
}

SDL_Texture* Game::loadImage(std::string_view path) {

	std::unique_ptr<SDL_Surface, Game::deleter> temp;
	temp.reset( IMG_Load(path.data()) );

	if (!temp)
		throw std::runtime_error(std::string("Can\'t load image from path: ") + std::string(path));

	SDL_Texture* texture{ SDL_CreateTextureFromSurface(renderer.get(), temp.get()) };

	if (!texture)
		throw std::runtime_error(std::string("Can\'t create image texture from path: ") + std::string(path));

	return texture;
}

void Game::renderMap() {
		
	SDL_RenderClear(renderer.get());
	SDL_SetRenderDrawColor(renderer.get(), 0, 255, 255, 150);

	SDL_Rect squareRect{ 0, 0, 500, 500 };

	int size{ 500 / 5 };

	auto myMap = map.getMatrix();

	for (int i{0}; i < 5; ++i) {
		for (int j{0}; j < 5; ++j) {
			SDL_Rect tile{ j * size, i * size, size, size };
			auto& texture = (myMap[i][j] == '1') ? wallTexture : grassTexture;
				SDL_RenderCopy(renderer.get(), texture.get(), nullptr, &tile);
		}
	}

	const Map::Coordinates& player = map.getPlayer();

	SDL_Rect tile{ player.j * size, player.i * size, size, size };
	SDL_RenderCopy(renderer.get(), playerTextre.get(), nullptr, &tile);

	SDL_RenderPresent(renderer.get());
}
