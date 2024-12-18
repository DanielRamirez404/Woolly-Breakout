#include "move.h"
#include "../../constants/constants.h"

Move::Move(float& variable, float limit) : axis{ variable }, end{ limit }, difference{ limit - variable } {} 

void Move::move() {
    axis = (timesCounter >= Constants::moveFrames - 1) ? end : axis + difference / Constants::moveFrames;
    ++timesCounter;
};
		
bool Move::isDone() {
    return timesCounter == Constants::moveFrames;
};