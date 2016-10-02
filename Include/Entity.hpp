#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "Interactable.hpp"

class Entity : public sf::Drawable, public sf::Transformable, public Interactable {
public:
	Entity();
	virtual void update(sf::Time);
	
	virtual sf::FloatRect borders() const;
	
	virtual void setDirection(float, float);
	virtual sf::Vector2f getDirection() const;
	
	virtual void setGrounded(float);
	virtual float getGrounded() const;
	
	virtual void setColor(sf::Color);
	
	virtual void applyGravity(bool);
	
protected:
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	virtual void attachTexture();
	
protected:
	sf::Sprite sprite;
	sf::Vector2f direction;
	sf::Color color;
	sf::Texture texture;
	
	bool gravityOn;
	float bottom;
};

#endif