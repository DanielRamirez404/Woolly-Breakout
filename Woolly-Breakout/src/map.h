#pragma once
#include <array>

class Map {

	public:

		struct Coordinates{

			int i{1};
			int j{1};

		};

		enum Direction {
			UP,
			DOWN,
			LEFT,
			RIGHT
		};

		using Matrix = std::array<std::array<char, 5>, 5>;
		
		const Matrix& getMatrix() const;
		const Coordinates& getPlayer() const;
		void movePlayer(Direction direction);

	private:

		Matrix matrix{
			{
				{'1', '0', '0', '0', '0'},
				{'1', '0', '1', '0', '0'},
				{'1', '0', '1', '1', '1'},
				{'1', '0', '0', '0', '1'},
				{'1', '1', '1', '1', '1'},
			}
		};

		Coordinates player;
};
