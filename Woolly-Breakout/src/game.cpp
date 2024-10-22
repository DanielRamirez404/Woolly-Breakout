#include "game.h"
#include "SDL.h"
#include <stdexcept>

Game::Game() {
	initializeLibraries();
}

void Game::initializeLibraries() {
		
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("SDL Initialization Error");

	SDL_Window* window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);

	if (!window)
		throw std::runtime_error("Window Initialization Error");

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!renderer)
		throw std::runtime_error("Renderer Initialization Error");

}

void Game::run() {
	//
}
