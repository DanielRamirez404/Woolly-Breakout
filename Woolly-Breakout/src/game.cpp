#include "game.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdexcept>
#include <memory>

Game::Game() {
	initializeLibraries();
}

void Game::initializeLibraries() {
		
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL Initialization Error");

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		throw std::runtime_error("SDL_Image Initialization Error");

	window.reset(SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN));

	if (!window)
		throw std::runtime_error("Window Initialization Error");

	renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));

	if (!renderer)
		throw std::runtime_error("Renderer Initialization Error");

}

void Game::run() {

	SDL_Event event{};

	SDL_SetRenderDrawColor(renderer.get(), 0, 255, 255, 150);

	SDL_Surface* temp = IMG_Load("../../res/grass.png");

	if (!temp)
		throw std::runtime_error("Cannot load image");

	grassTexture.reset(SDL_CreateTextureFromSurface(renderer.get(), temp));
	SDL_FreeSurface(temp);

	if (!grassTexture)
	{
		throw std::runtime_error("cannot load image");
	}

	SDL_Rect fullBoardRect{ 0, 0, 800, 800 };

	SDL_Rect squareRect{ 0, 0, 800, 800 };
	SDL_RenderClear(renderer.get());
	SDL_RenderCopy(renderer.get(), grassTexture.get(), nullptr, &squareRect);
	SDL_RenderPresent(renderer.get());

	while (true) {

		while (SDL_WaitEvent(&event)) {

			if (event.type == SDL_QUIT)
				return;

		}

	}
}
