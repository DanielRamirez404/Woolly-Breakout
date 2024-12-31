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

void Player::setCoordinates(const Coordinates<float>& newCoordinates) {
	coordinates = newCoordinates;
}

const Coordinates<int> Player::getRoundedCoordinates() const {
	return { static_cast<int>(coordinates.i), static_cast<int>(coordinates.j) };
}

bool Player::isMoving() {
    return movement.has_value() && !movement.value().isDone();
}

void Player::queueMove(Direction direction) {
    queuedDirection = direction;
}

std::optional<Coordinates<int>> Player::getTargetedCoordinates() {
	
	if (!queuedDirection)
		return std::nullopt;
	
	Coordinates<float> targetedCoordinates{};

	switch (queuedDirection.value()) {
		case Direction::UP:
			targetedCoordinates = { coordinates.i - 1, coordinates.j };
			break;

		case Direction::DOWN:
			targetedCoordinates = { coordinates.i + 1, coordinates.j };
			break;

		case Direction::LEFT:
			targetedCoordinates = { coordinates.i, coordinates.j - 1 };
			break;
		
		case Direction::RIGHT:
			targetedCoordinates = { coordinates.i, coordinates.j + 1 };
			break;
	}

	return Coordinates<int>{ static_cast<int>(targetedCoordinates.i), static_cast<int>(targetedCoordinates.j) };
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