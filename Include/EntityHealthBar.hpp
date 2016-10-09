#ifndef ENTITYHEALTHBAR_HPP
#define ENTITYHEALTHBAR_HPP

#include "Entity.hpp"

#include <string>

class EntityHealthBar : public Entity {
public:
	EntityHealthBar();
	void update(sf::Time);
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
	void setColor(sf::Color);
	
	void setHealth(unsigned int);
	
protected:
	void attachTexture(std::string);
	void draw(sf::RenderTarget&, sf::RenderStates) const;
	
	sf::Sprite heartOne;
	sf::Sprite heartTwo;
	sf::Sprite heartThree;
	sf::Sprite heartFour;
	
	unsigned int health;
	sf::Texture heartTexture;
};

#endif