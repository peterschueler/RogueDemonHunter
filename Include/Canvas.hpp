#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <SFML/Graphics.hpp>

#include "Command.hpp"

class Canvas : public sf::NonCopyable {
public:
	virtual bool update(sf::Time) = 0;
	virtual void draw() = 0;
	
	virtual void input(Command*) = 0;
	virtual void stop() = 0;
};

#endif