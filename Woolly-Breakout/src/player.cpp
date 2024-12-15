#include "player.h"
#include "map-utilities.h"

Player::Player(const Coordinates<int>& mapCoordinates)
    : coordinates{ static_cast<float>(mapCoordinates.i), static_cast<float>(mapCoordinates.j) } {}

const Coordinates<float>& Player::getCoordinates() const {
    return coordinates;
}

void Player::move(Direction direction) {
    switch (direction)
	{
		case Direction::UP:
			--coordinates.i;
			break;

		case Direction::DOWN:
			++coordinates.i;
			break;

		case Direction::LEFT:
			--coordinates.j;
			break;
		
		case Direction::RIGHT:
			++coordinates.j;
			break;
	
	}
}