#include "map.h"
#include "../../constants/constants.h"
#include "../../constants/notation.h"
#include "utilities.h"
#include "../entities/safe-zone.h"
#include <vector>
#include <utility>
#include <string>

Map::Map(bool isSinglePlayer) {

	if (!isSinglePlayer)
		secondPlayer.emplace(player.getRoundedCoordinates());

	std::vector<Coordinates<int>> keys{};
	keys.reserve(Constants::SafeZone::totalKeys);

	Coordinates<int> door{};

	for (int i{0}; i < Constants::Map::Matrix::size || (safeZone && keys.size() == Constants::SafeZone::totalKeys); ++i)
		for (int j{0}; j < Constants::Map::Matrix::size; ++j) {

			char tile{ matrix[i][j] };

			if (tile == Notation::characters["key"])
				keys.push_back({i, j});
			else if (tile == Notation::characters["door"])
				door = {i, j};		
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
	return tileValue == Notation::characters["grass"] || tileValue == Notation::characters["key"] || tileValue == Notation::characters["exit"];
}

void Map::handlePlayerInteractions(Player& handledPlayer, const std::function<void()>& onWin) {
	if (handledPlayer.isMoving()) {
		handledPlayer.keepMoving();
		handlePickingKeyUp(handledPlayer.getRoundedCoordinates());
		handleWinCheking(handledPlayer.getRoundedCoordinates(), onWin);
	} else {
		const auto target{ handledPlayer.getTargetedCoordinates() };
		
		if (target && isLegalMove(target.value()))
			handledPlayer.startMove();
	}
}

void Map::handleWinCheking(const Coordinates<int>& coordinates, const std::function<void()>& onWin) {
	if (matrix[coordinates.i][coordinates.j] == Notation::characters["exit"]) {
		events.push( { Event::Win, "Congratz!" } );
		onWin();
	}
}

std::string Map::toString() {
	std::string string{""};

	for (int i{0}; i < Constants::Map::Matrix::size ; ++i) {
		for (int j{0}; j < Constants::Map::Matrix::size ; ++j) {
			string += matrix[i][j];
		}
	}

	return string;
}

void Map::readString(std::string& string) {
	std::vector<Coordinates<int>> keys{};
	Coordinates<int> door{-1, -1};
	keys.reserve(Constants::SafeZone::totalKeys);

	for (int i{0}; i < string.size(); ++i) {
		int i_index{ i / Constants::Map::Matrix::size };
		int j_index{ i % Constants::Map::Matrix::size };

		char& position{ matrix[i_index][j_index] };

		position = string[i];

		if (position == Notation::characters["key"])
			keys.push_back({i_index, j_index});
		else if (position == Notation::characters["door"]) 
			door = {i_index, j_index};
	}

	if (door == Coordinates<int>{-1, -1})
		return;

	safeZone = {std::move(door), keys};
}

Player& Map::getPlayer() {
	return player;
}

const Player& Map::getPlayer() const {
	return player;
}

Player& Map::getSecondPlayer() {
	return secondPlayer.value();
}

const Player& Map::getSecondPlayer() const {
	return secondPlayer.value();
}

const char Map::operator()(int i, int j) const {
	return matrix[i][j];
}

bool Map::isThereAnyEvent() {
	return !events.empty();
}

std::pair<Map::Event, std::string> Map::getFirstEvent() {
	auto event{ events.front() };
	events.pop();
	return event;
}

void Map::addEvent(const std::pair<Event, std::string>& event) {
	events.push(event);
}


void Map::handlePickingKeyUp(std::string& eventString) {
	handlePickingKeyUp(Coordinates<int>{ eventString });
}

void Map::handlePickingKeyUp(const Coordinates<int>& coordinates) {
	if (safeZone && safeZone.value().isKey(coordinates)) {
		safeZone.value().pickKeyUp(coordinates);
		events.push( { Event::PickUpKey, coordinates.toString() } );
		matrix[coordinates.i][coordinates.j] = Notation::characters["grass"];

		if (!safeZone.value().isOpen()) {
			const auto& doorCoordinates = safeZone.value().getDoor();
			matrix[doorCoordinates.i][doorCoordinates.j] = Notation::characters["exit"];
			safeZone.reset();
		}
	}
}
