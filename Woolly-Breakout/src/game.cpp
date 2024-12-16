#include "game.h"
#include "map.h"
#include "player.h"
#include "map-utilities.h"
#include "SDL.h"
#include <functional>

void Game::run() {
	window.startGameLoop(std::bind(&Game::handleEvents, this, std::placeholders::_1), std::bind(&Game::handleLogic, this), map);
}

void Game::handleEvents(SDL_Event& event) {

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		
			case SDLK_w:
			case SDLK_UP:
				map.getPlayer().startMove(Direction::UP);
				break;

			case SDLK_a:
			case SDLK_LEFT:
				map.getPlayer().startMove(Direction::LEFT);
				break;

			case SDLK_s:
			case SDLK_DOWN:
				map.getPlayer().startMove(Direction::DOWN);
				break;

			case SDLK_d:
			case SDLK_RIGHT:
				map.getPlayer().startMove(Direction::RIGHT);
				break;
		
			default:
				break;
		}
	}
}

void Game::handleLogic() {
	Player& player = map.getPlayer();

	if (player.isMoving()) 
		player.keepMoving();
}