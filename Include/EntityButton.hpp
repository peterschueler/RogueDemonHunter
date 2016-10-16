#ifndef ENTITYBUTTON_HPP
#define ENTITYBUTTON_HPP

#include "Entity.hpp"

#include <string>

class EntityButton : public Entity {
public:
	enum Type {
		doorKey,
		healthPod,
		doom_one,
		doom_two,
		doom_three,
		doom_four
	};
public:
	EntityButton();
	// x, y, and type
	EntityButton(int, int, int);
	void update(sf::Time);
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
	EntityButton::Type getType() const;
	
protected:
	void attachTexture(std::string);
	
private:
	Type type;
};

#endif