#pragma once
#include "constants.h"

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

enum Sense {
	POS,
	NEG
};

class Move {

	public:

		Move(float& variable, float limit) : axis{ variable }, end{ limit },
			difference{ limit - variable }, 
			sense{ (limit > variable) ? Sense::POS : Sense::NEG } {};

		void move() { axis += static_cast<float>(difference) / 15; };
		bool isDone() { 
				return (sense == Sense::POS) ? axis > end : axis < end;
			};

	private:

		float& axis;
		float end{};
		float difference{};
		Sense sense{};
};