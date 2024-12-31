#pragma once
#include "../entities/player.h"
#include "../entities/safe-zone.h"
#include "utilities.h"
#include "../../constants/constants.h"
#include <array>
#include <optional>
#include <string>

class Map {

	public:

		Map();

		using Matrix = std::array<std::array<char, Constants::Map::Matrix::size>, Constants::Map::Matrix::size>;
		
		int getPickedUpKeys() const;
		bool isSafeZoneOpen() const;
		bool isLegalMove(const Coordinates<int>& coordinates) const;

		void handleInteractions();

		std::string toString();
		void readString(std::string string);

		Player& getPlayer();
		const Player& getPlayer() const;

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
		std::optional<SafeZone> safeZone{ std::nullopt };
		
};
