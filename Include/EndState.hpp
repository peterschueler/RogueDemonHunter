#ifndef ENDSTATE_HPP
#define ENDSTATE_HPP

#include "State.hpp"
#include "EndMenu.hpp"
#include "InputHandler.hpp"

class EndState : public State {
public:
	EndState(sf::RenderWindow& win, bool);
	
	bool processInput(sf::Event& event);	
	bool update(sf::Time delta);
	void onEntry(State* previousState);
	State* onExit();
	void render();
	
private:
	sf::RenderWindow* window;
	EndMenu menu;
	InputHandler handler;
	
	bool isPaused;
};

#endif