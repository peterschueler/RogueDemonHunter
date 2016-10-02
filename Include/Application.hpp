#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "State.hpp"

#include "Settings.hpp"

class Application {
public:
	Application();
	Application(Settings&);
	void run();
	
private:
	void processInput();
	void update(sf::Time);
	void render();
	
	void enterState(State*);
	
private:
	sf::RenderWindow window;
	std::vector<State> States;
	State* currentState;
	static const sf::Time secondsFramesRatio;
};

#endif