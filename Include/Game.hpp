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
	
	bool getWin() { return didWin; };
	
private:
	void checkCollisions();
	void changeLevels(sf::Time);
	void moveMonsters(sf::Time);
	
	void setLevelCounter(unsigned int);
	
private:
	sf::RenderWindow& window;
	sf::FloatRect bounds;
		
	sf::Sprite levelCounter;
	sf::Texture levelCounterTexture;
	
	EntityHeroine* heroine;
	EntityHealthBar* healthBar;
	unsigned int currentHealth;
	bool gameOver;
	bool didWin;
	int bossPoints;
	int bossScaler;
	
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
	
	sf::SoundBuffer stepBuffer;
	sf::Sound stepSound;
	sf::SoundBuffer hitBuffer;
	sf::Sound hitSound;
	sf::SoundBuffer healthBuffer;
	sf::Sound healthSound;
	sf::SoundBuffer keyBuffer;
	sf::Sound keySound;
};

#endif