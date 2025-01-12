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
	return tileValue == Notation::characters["grass"] || tileValue == Notation::characters["key"];
}

void Map::handleInteractions() {
	handlePlayerInteractions(player);

	if (secondPlayer)
		handlePlayerInteractions(secondPlayer.value());
}

void Map::handlePlayerInteractions(Player& handledPlayer) {
	if (handledPlayer.isMoving()) {
		handledPlayer.keepMoving();
		handlePickingKeyUp(handledPlayer.getRoundedCoordinates());
	} else {
		const auto target{ handledPlayer.getTargetedCoordinates() };
		
		if (target && isLegalMove(target.value()))
			handledPlayer.startMove();
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

std::string Map::getStringFrom(const Player& handledPlayer) {
	return coordinateToString(handledPlayer.getCoordinates());
}

std::string Map::getPlayerString() {
	return getStringFrom(player);
}

std::string Map::getSecondPlayerString() {
	return getStringFrom(secondPlayer.value());
}

void Map::readStringFor(std::string& string, Player& handledPlayer) {
	int commaIndex{ static_cast<int>(string.find(',')) };

	float i_player_coordinate{ std::stof( string.substr(0, commaIndex) ) };
	float j_player_coordinate{ std::stof( string.substr(commaIndex + 1, string.size() - commaIndex - 1) ) };

	handledPlayer.setCoordinates({i_player_coordinate, j_player_coordinate});
}

void Map::readPlayerString(std::string& string) {
	readStringFor(string, player);
}

void Map::readSecondPlayerString(std::string& string) {
	readStringFor(string, secondPlayer.value());
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

std::string Map::coordinateToString(const Coordinates<int>& coordinates) {
	std::string string{""};

	string.append( std::to_string(coordinates.i) );
	string += ',';
	string.append( std::to_string(coordinates.j) );

	return string;
}

std::string Map::coordinateToString(const Coordinates<float>& coordinates) {
	std::string string{""};

	string.append( std::to_string(coordinates.i) );
	string += ',';
	string.append( std::to_string(coordinates.j) );

	return string;
}

bool Map::isThereAnyEvent() {
	return !events.empty();
}

std::pair<Map::Event, std::string> Map::getFirstEvent() {
	auto event{ events.front() };
	events.pop();
	return event;
}

const Coordinates<int> Map::stringToCoordinates(std::string& string) {
	int commaIndex{ static_cast<int>(string.find(',')) };

	int i{ std::stoi( string.substr(0, commaIndex) ) };
	int j{ std::stoi( string.substr(commaIndex + 1, string.size() - commaIndex - 1) ) };

	return { i, j };
}

void Map::handlePickingKeyUp(std::string& eventString) {
	handlePickingKeyUp(stringToCoordinates(eventString));
}

void Map::handlePickingKeyUp(const Coordinates<int>& coordinates) {
	if (safeZone && safeZone.value().isKey(coordinates)) {
		safeZone.value().pickKeyUp(coordinates);
		events.push( {Event::PickUpKey, coordinateToString(coordinates)} );
		matrix[coordinates.i][coordinates.j] = Notation::characters["grass"];

		if (!safeZone.value().isOpen()) {
			const auto& doorCoordinates = safeZone.value().getDoor();
			matrix[doorCoordinates.i][doorCoordinates.j] = Notation::characters["grass"];
			safeZone.reset();
		}
	}
}
