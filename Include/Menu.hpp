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
	void animate();
	
private:
	enum AnimationStep {
		first,
		second,
		third,
		fourth,
		fifth,
		sixth
	};
	AnimationStep currentStep;
	float animationTimer;
	
	sf::RenderWindow& window;
	sf::FloatRect bounds;
	
	sf::Music theme;
	
	sf::Sprite sprite;
	sf::Texture texture;
	
	sf::Sprite blinky;
	sf::Texture bl_texture;
};

#endif