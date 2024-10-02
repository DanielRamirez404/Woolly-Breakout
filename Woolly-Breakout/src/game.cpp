#include "game.h"
#include "SDL.h"
#include <iostream>

Game::Game() {

}

Game::~Game() {

}

void Game::run() {

	if (SDL_Init(SDL_INIT_VIDEO) == 0)
		std::cout << "I\'m running!\n";
}
