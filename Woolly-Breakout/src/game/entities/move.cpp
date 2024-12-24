#include "move.h"
#include "../../constants/constants.h"

Move::Move(float& variable, float limit) : axis{ variable }, end{ limit }, difference{ limit - variable } {} 

void Move::move() {
    axis = (timesCounter >= Constants::Frames::perMove - 1) ? end : axis + difference / Constants::Frames::perMove;
    ++timesCounter;
};
		
bool Move::isDone() {
    return timesCounter == Constants::Frames::perMove;
};