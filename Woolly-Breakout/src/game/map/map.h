#pragma once
#include "../entities/player.h"
#include "../entities/safe-zone.h"
#include "utilities.h"
#include "../../constants/constants.h"
#include <array>

class Map {

	public:


		Map();

		using Matrix = std::array<std::array<char, Constants::Map::Matrix::size>, Constants::Map::Matrix::size>;
		
		int getPickedUpKeys() const;
		bool isSafeZoneOpen() const;

		void handleInteractions();

		Player& getPlayer();
		const Player& getPlayer() const;

		const char operator()(int i, int j) const;

	private:

		Matrix matrix{
			{
				{'2', '0', '3', '0', '0'},
				{'1', '0', '1', '0', '0'},
				{'1', '0', '1', '0', '1'},
				{'1', '0', '0', '0', '3'},
				{'1', '3', '1', '1', '1'},
			}
		};

		Player player{ Coordinates<int>{ 1, 1 } };
		SafeZone safeZone{};
	
};
