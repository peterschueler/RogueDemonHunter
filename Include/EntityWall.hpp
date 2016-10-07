#ifndef ENTITYWALL_HPP
#define ENTITYWALL_HPP

#include "Entity.hpp"

#include <string>

class EntityWall : public Entity {
public:
	EntityWall();
	// x, y, type
	EntityWall(int, int, int);
	void update(sf::Time);
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
protected:
	void attachTexture(std::string);
	
private:
	enum Type {
		outer_corner,
		outer_first,
		outer_second,
		inner_first,
		inner_second,
		inner_corner
	};
	Type type;
};

#endif