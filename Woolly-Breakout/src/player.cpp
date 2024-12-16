#include "player.h"
#include "map-utilities.h"
#include <optional>

Player::Player(const Coordinates<int>& mapCoordinates)
    : coordinates{ static_cast<float>(mapCoordinates.i), static_cast<float>(mapCoordinates.j) } {}

const Coordinates<float>& Player::getCoordinates() const {
    return coordinates;
}

bool Player::isMoving() {
    return movement.has_value() && !movement.value().isDone();
}

void Player::startMove(Direction direction) {
    switch (direction) {
		case Direction::UP:
			movement.emplace(coordinates.i, coordinates.i - 1);
			break;

		case Direction::DOWN:
			movement.emplace(coordinates.i, coordinates.i + 1);
			break;

		case Direction::LEFT:
			movement.emplace(coordinates.j, coordinates.j - 1);
			break;
		
		case Direction::RIGHT:
			movement.emplace(coordinates.j, coordinates.j + 1);
			break;
	
	}
}

void Player::keepMoving() {
    movement.value().move();
}


void Player::stopMove() {
    movement = std::nullopt;
}