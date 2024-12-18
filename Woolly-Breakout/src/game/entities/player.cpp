#include "player.h"
#include "../map/utilities.h"
#include "move.h"
#include <optional>
#include <utility>

Player::Player(const Coordinates<int>& mapCoordinates)
    : coordinates{ static_cast<float>(mapCoordinates.i), static_cast<float>(mapCoordinates.j) } {}

const Coordinates<float>& Player::getCoordinates() const {
    return coordinates;
}

bool Player::isMoving() {
    return movement.has_value() && !movement.value().isDone();
}

void Player::queueMove(Direction direction) {
    queuedDirection = direction;
}

void Player::startMove() {
    if (!queuedDirection.has_value())
        return;

    switch (queuedDirection.value()) {
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

    queuedDirection.reset();
    keepMoving();
}

void Player::keepMoving() {
    movement.value().move();
}


void Player::stopMove() {
    movement = std::nullopt;
}