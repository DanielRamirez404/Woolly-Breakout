#include "game.h"
#include "map.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdexcept>
#include <memory>
#include <functional>

void Game::run() {
	window.startGameLoop( std::bind(&Game::handleEvents, this, std::placeholders::_1), map );
}

void Game::handleEvents(SDL_Event& event) {
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
}