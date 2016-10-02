#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "State.hpp"
#include "InputHandler.hpp"
#include "Menu.hpp"

class MenuState : public State {
public:
	MenuState(sf::RenderWindow&);
	
	bool processInput(sf::Event&);
	bool update(sf::Time);
	void onEntry(State*);
	State* onExit();
	void render();
	
private:
	sf::RenderWindow* window;
	InputHandler handler;
	
	bool gameStarted;
	
	Menu menu;
};

#endif