#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "State.hpp"
#include "Game.hpp"
#include "InputHandler.hpp"

class GameState : public State {
public:
	GameState(sf::RenderWindow&);
	
	bool processInput(sf::Event&);
	bool update(sf::Time);
	void onEntry(State*);
	State* onExit();
	void render();
	
private:
	sf::RenderWindow* window;
	InputHandler handler;
	
	bool isPaused;
	
	Game game;
};

#endif