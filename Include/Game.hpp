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
	void changeLevels(sf::Time);
	void moveMonsters(sf::Time);
	
private:
	sf::RenderWindow& window;
	sf::FloatRect bounds;
	
	EntityHeroine* heroine;
	
	Level level;
	
	sf::Vector2f movedDistance;
	float moved_y;
	float moved_x;
	bool movingToNextLevel;
	unsigned int currentLevel;
	
	float monsterLoop;
	
	sf::View viewPort;
	sf::Sprite background;
	sf::Texture backgroundTexture;
};

#endif