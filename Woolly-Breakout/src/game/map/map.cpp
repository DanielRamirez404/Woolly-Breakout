#include "map.h"
#include "../../constants/constants.h"
#include "utilities.h"
#include "../entities/safe-zone.h"

Map::Map() {
	for (int i{0}; i < Constants::mapSize; ++i)
		for (int j{0}; j < Constants::mapSize; ++j)
			switch (matrix[i][j]) {
				case '3':
					safeZone.addKey({i, j});
					break;

				case '2':
					safeZone.setDoor({i, j});
					break;

				default:
					break;
			}
};

const Map::Matrix& Map::getMatrix() const {
	return matrix;
}

const Coordinates<float>& Map::getPlayer() const {
	return player.getCoordinates();
}

Player& Map::getPlayer() {
	return player;
}

SafeZone& Map::getSafeZone() {
	return safeZone;
}

const SafeZone& Map::getSafeZone() const {
	return safeZone;
}