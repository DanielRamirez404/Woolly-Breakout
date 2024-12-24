#include "map.h"
#include "../../constants/constants.h"
#include "utilities.h"
#include "../entities/safe-zone.h"

Map::Map() {
	for (int i{0}; i < Constants::Map::Matrix::size; ++i)
		for (int j{0}; j < Constants::Map::Matrix::size; ++j)
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

int Map::getPickedUpKeys() const {
	return safeZone.getPickedUpKeys();
}

bool Map::isSafeZoneOpen() const {
	return safeZone.isOpen();
}

void Map::handleInteractions() {
	if (player.isMoving()) {
		player.keepMoving();

		Coordinates<int> playerCoordinates = { player.getRoundedCoordinates() };

		if (safeZone.isKey(playerCoordinates)) {
			safeZone.pickKeyUp(playerCoordinates);
			matrix[playerCoordinates.i][playerCoordinates.j] = '0';
		}

	} else {
		player.startMove();
	}
}

Player& Map::getPlayer() {
	return player;
}

const Player& Map::getPlayer() const {
	return player;
}

const char Map::operator()(int i, int j) const {
	return matrix[i][j];
}