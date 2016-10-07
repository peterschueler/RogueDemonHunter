#include "../Include/InputHandler.hpp"
#include "../Include/CommandMove.hpp"

#include <iostream>

Command* InputHandler::handleInput(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Left) {
			return new CommandMove(-40.f, 0.f);
		} else if (event.key.code == sf::Keyboard::Right) {
			return new CommandMove(40.f, 0.f);
		} else if (event.key.code == sf::Keyboard::Up) {
			return new CommandMove(0.f, -40.f);
		} else if (event.key.code == sf::Keyboard::Down) {
			return new CommandMove(0.f, 40.f);
		}
	}
	return new CommandMove(0,0);
}