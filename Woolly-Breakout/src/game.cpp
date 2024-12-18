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

	Player& player = map.getPlayer();

	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		
			case SDLK_w:
			case SDLK_UP:
				player.queueMove(Direction::UP);
				break;

			case SDLK_a:
			case SDLK_LEFT:
				player.queueMove(Direction::LEFT);
				break;

			case SDLK_s:
			case SDLK_DOWN:
				player.queueMove(Direction::DOWN);
				break;

			case SDLK_d:
			case SDLK_RIGHT:
				player.queueMove(Direction::RIGHT);
				break;
		
			default:
				break;
		}
	}
}

void Game::handleLogic() {
	Player& player = map.getPlayer();
	SafeZone& safeZone = map.getSafeZone();

	if (player.isMoving()) {
		player.keepMoving();

		Coordinates<int> playerCoordinates = { static_cast<int>(player.getCoordinates().i), static_cast<int>(player.getCoordinates().j) };

		if (safeZone.isKey(playerCoordinates))
			safeZone.pickKeyUp(playerCoordinates);

	} else {
		player.startMove();
	}
}