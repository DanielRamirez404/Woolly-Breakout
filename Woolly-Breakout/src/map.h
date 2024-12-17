#pragma once
#include "player.h"
#include "safe-zone.h"
#include "map-utilities.h"
#include <array>

class Map {

	public:


		Map();

		using Matrix = std::array<std::array<char, 5>, 5>;
		
		const Matrix& getMatrix() const;
		const Coordinates<float>& getPlayer() const;
		Player& getPlayer();
		SafeZone& getSafeZone();
		const SafeZone& getSafeZone() const;

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
