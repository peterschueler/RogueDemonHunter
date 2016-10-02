#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Entities.hpp"
#include "Interactable.hpp"

class Command {
public:
	virtual void execute(Interactable*) = 0;
};

#endif