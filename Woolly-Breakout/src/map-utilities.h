#pragma once

template <typename T>
struct Coordinates {
	T i{};
	T j{};
};

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};
