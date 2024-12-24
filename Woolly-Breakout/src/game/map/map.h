#pragma once
#include "../entities/player.h"
#include "../entities/safe-zone.h"
#include "utilities.h"
#include <array>

class Map {

	public:


		Map();

		using Matrix = std::array<std::array<char, 5>, 5>;
		
		const Matrix& getMatrix() const;
		const Coordinates<float>& getPlayerCoordinates() const;
		int getPickedUpKeys() const;
		bool isSafeZoneOpen() const;

		Matrix& getMatrix();
		Player& getPlayer();
		SafeZone& getSafeZone();

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
