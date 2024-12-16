#pragma once

class Move {

	public:

		Move(float& variable, float limit);

		void move();
		
        bool isDone();

	private:

		float& axis;
		float end{};
		float difference{};
        int timesCounter{0};
};