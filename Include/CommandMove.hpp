#ifndef MOVE_COMMAND_HPP
#define MOVE_COMMAND_HPP

#include "Command.hpp"

class CommandMove : public Command {
public:
	CommandMove(float, float);
	void execute(Interactable*);
	
private:
	float x;
	float y;
};

#endif