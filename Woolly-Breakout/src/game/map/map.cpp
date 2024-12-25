#include "map.h"
#include "../../constants/constants.h"
#include "utilities.h"
#include "../entities/safe-zone.h"
#include <vector>
#include <utility>

Map::Map() {

	std::vector<Coordinates<int>> keys{};
	keys.reserve(Constants::SafeZone::totalKeys);

	Coordinates<int> door{};

	for (int i{0}; i < Constants::Map::Matrix::size || (safeZone && keys.size() == Constants::SafeZone::totalKeys); ++i)
		for (int j{0}; j < Constants::Map::Matrix::size; ++j)
			switch (matrix[i][j]) {
				case '3':
					keys.push_back({i, j});
					break;

				case '2':
					door = {i, j};
					break;

				default:
					break;
			}

	safeZone = {std::move(door), keys};
};

int Map::getPickedUpKeys() const {
	return (safeZone) ? safeZone.value().getPickedUpKeys() : Constants::SafeZone::totalKeys;
}

bool Map::isSafeZoneOpen() const {
	return !safeZone;
}

bool Map::isOutOfBounds(int i, int j) {
	return (i < 0 || j < 0 || i >= Constants::Map::Matrix::size || j >= Constants::Map::Matrix::size);	
}

bool Map::isLegalMove(const Coordinates<int>& coordinates) const {

	if (isOutOfBounds(coordinates.i, coordinates.j))
		return false;

	char tileValue{ matrix[coordinates.i][coordinates.j] };
	return tileValue == '0' || tileValue == '3';
}

void Map::handleInteractions() {
	if (player.isMoving()) {
		player.keepMoving();

		if (!safeZone)
			return;

		Coordinates<int> playerCoordinates = { player.getRoundedCoordinates() };

		if (safeZone.value().isKey(playerCoordinates)) {
			safeZone.value().pickKeyUp(playerCoordinates);
			matrix[playerCoordinates.i][playerCoordinates.j] = '0';

			if (!safeZone.value().isOpen()) {
				const auto& doorCoordinates = safeZone.value().getDoor();
				matrix[doorCoordinates.i][doorCoordinates.j] = '0';
				safeZone.reset();
			}
		}

	} else {
		const auto target{ player.getTargetedCoordinates() };
		
		if (target && isLegalMove(target.value()))
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