#include "../Include/CommandMove.hpp"

#include <iostream>

CommandMove::CommandMove(float vx, float vy) : x(vx), y(vy) {
}

void CommandMove::execute(Interactable* inter) {
	inter->setDirection(x, y);
}