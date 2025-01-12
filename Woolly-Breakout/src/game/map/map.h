#pragma once
#include "../entities/player.h"
#include "../entities/safe-zone.h"
#include "utilities.h"
#include "../../constants/constants.h"
#include <array>
#include <optional>
#include <string>
#include <queue>
#include <utility>

class Map {

	public:

		enum Event {
			PickUpKey,
			Win
		};

		Map(bool isSinglePlayer = true);

		using Matrix = std::array<std::array<char, Constants::Map::Matrix::size>, Constants::Map::Matrix::size>;
		
		int getPickedUpKeys() const;
		bool isSafeZoneOpen() const;
		bool isLegalMove(const Coordinates<int>& coordinates) const;

		void handlePlayerInteractions(Player& handledPlayer);
		void handleInteractions();

		bool isThereAnyEvent();
		std::pair<Event, std::string> getFirstEvent();
		void handlePickingKeyUp(std::string& eventString);
		void handlePickingKeyUp(const Coordinates<int>& coordinates);
		
		std::string toString();
		std::string getPlayerString();
		std::string getSecondPlayerString();

		void readPlayerString(std::string& string);
		void readSecondPlayerString(std::string& string);
		void readString(std::string& string);

		Player& getPlayer();
		const Player& getPlayer() const;
		Player& getSecondPlayer();
		const Player& getSecondPlayer() const;

		const char operator()(int i, int j) const;
		static bool isOutOfBounds(int i, int j); 

	private:

		Matrix matrix{
			{
				{'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
				{'0', '1', '1', '1', '0', '1', '0', '0', '0', '0'},
				{'0', '0', '3', '1', '0', '0', '0', '0', '1', '0'},
				{'1', '1', '1', '1', '1', '0', '1', '0', '1', '0'},
				{'0', '3', '1', '0', '0', '0', '1', '0', '1', '0'},
				{'0', '1', '1', '0', '3', '0', '1', '0', '1', '3'},
				{'0', '1', '0', '0', '0', '0', '1', '0', '1', '0'},
				{'0', '1', '0', '0', '0', '0', '1', '0', '1', '1'},
				{'0', '0', '0', '1', '1', '0', '1', '0', '1', '1'},
				{'1', '3', '1', '0', '0', '0', '0', '2', '0', '1'},
			}
		};

		Player player{ Coordinates<int>{ 0, 5 } };
		std::optional<Player> secondPlayer{ std::nullopt };
		std::optional<SafeZone> safeZone{ std::nullopt };

		std::queue<std::pair<Event, std::string>> events{};

		std::string getStringFrom(const Player& handledPlayer);
		void readStringFor(std::string& string, Player& handledPlayer);

		std::string coordinateToString(const Coordinates<int>& coordinates);
		std::string coordinateToString(const Coordinates<float>& coordinates);
		const Coordinates<int> stringToCoordinates(std::string& string);
};
