#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <SFML/Window/Event.hpp>

#include "Command.hpp"

class InputHandler {
public:
	Command* handleInput(const sf::Event&);
};

#endif