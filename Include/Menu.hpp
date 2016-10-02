#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Canvas.hpp"

class Menu : public Canvas {
public:
	explicit Menu(sf::RenderWindow&);
	
	bool update(sf::Time);
	void draw();
	
	void input(Command*) {}
	void stop() {}
	
private:
	sf::RenderWindow& window;
	sf::FloatRect bounds;
};

#endif