#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "Canvas.hpp"
#include "Entities.hpp"

class Game : public Canvas {
public:
	explicit Game(sf::RenderWindow&);
	
	bool update(sf::Time time);
	void draw();
	
	void input(Command*);
	void stop() {}
	
private:
	sf::RenderWindow& window;
	sf::FloatRect bounds;
};

#endif