#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "Canvas.hpp"
#include "Entities.hpp"
#include "Level.hpp"

class Game : public Canvas {
public:
	explicit Game(sf::RenderWindow&);
	
	bool update(sf::Time time);
	void draw();
	
	void input(Command*);
	void stop() {}
	
private:
	void checkCollisions();
	
private:
	sf::RenderWindow& window;
	sf::FloatRect bounds;
	
	EntityHeroine* heroine;
	
	Level currentLevel;
	
	sf::View viewPort;
	sf::Sprite background;
	sf::Texture backgroundTexture;
};

#endif