#pragma once
#include "constants.h"

template <typename T>
struct Coordinates {
	T i{};
	T j{};

	bool operator==(Coordinates<T>const& coordinates) const {
		return coordinates.i == i && coordinates.j == j;
	}
};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};