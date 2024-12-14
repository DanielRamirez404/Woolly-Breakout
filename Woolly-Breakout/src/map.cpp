#include "map.h"

const Map::Matrix& Map::getMatrix() {
	return matrix;
}

const Map::Coordinates& Map::getPlayer() {
	return player;
}

void Map::movePlayer(Map::Direction direction) {
	using Dir = Map::Direction;
	
	switch (direction)
	{
		case Dir::UP:
			--player.i;
			break;

		case Dir::DOWN:
			++player.i;
			break;

		case Dir::LEFT:
			--player.j;
			break;
		
		case Dir::RIGHT:
			++player.j;
			break;
	
	}
}
