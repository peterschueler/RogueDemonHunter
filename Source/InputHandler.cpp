#include "../Include/InputHandler.hpp"
#include "../Include/CommandMove.hpp"

#include <iostream>

Command* InputHandler::handleInput(const sf::Event& event) {
	return new CommandMove(0,0);
}