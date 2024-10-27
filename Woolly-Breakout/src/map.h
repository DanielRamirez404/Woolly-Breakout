#pragma once
#include <array>

class Map {

	public:

		using Matrix = std::array<std::array<char, 5>, 5>;
		
		const Matrix& getMatrix();

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
};
