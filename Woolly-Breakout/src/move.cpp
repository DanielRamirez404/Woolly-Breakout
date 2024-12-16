#include "move.h"
#include "constants.h"

#include <iostream>

Move::Move(float& variable, float limit) : axis{ variable }, end{ limit }, difference{ limit - variable } {} 

void Move::move() {
    axis = (timesCounter >= Constants::moveFrames - 1) ? end : axis + difference / Constants::moveFrames;
    ++timesCounter;

    std::cout << "axis: "<< axis << "\nend: " << end << '\n';
};
		
bool Move::isDone() {
    return timesCounter == Constants::moveFrames;
};