#ifndef ENTITYBUTTON_HPP
#define ENTITYBUTTON_HPP

#include "Entity.hpp"

#include <string>

class EntityButton : public Entity {
public:
	EntityButton();
	// x, y, and type
	EntityButton(int, int, int);
	void update(sf::Time);
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
protected:
	void attachTexture(std::string);
	
private:
	enum Type {
		doorKey,
		healthPod,
		pausePod
	};
	Type type;
};

#endif