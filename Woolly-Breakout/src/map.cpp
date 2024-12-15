#include "map.h"
#include "map-utilities.h"

const Map::Matrix& Map::getMatrix() const {
	return matrix;
}

const Coordinates<float>& Map::getPlayer() const {
	return player.getCoordinates();
}

void Map::movePlayer(Direction direction) {
	player.move(direction);
}
