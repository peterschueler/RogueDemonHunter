#ifndef ENTITYWALL_HPP
#define ENTITYWALL_HPP

#include "Entity.hpp"

#include <string>

class EntityWall : public Entity {
public:
	enum Type {
		outer_corner,
		outer_first,
		outer_second,
		outer_third,
		outer_door
	};
	enum Facing {
		north,
		east,
		west,
		south
	};
	
public:
	EntityWall();
	// x, y, type
	EntityWall(int, int, int);
	void update(sf::Time);
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
	void setType(EntityWall::Type);
	Type getType() const;
	Facing getFacing() const;
	sf::Vector2f getRawPosition() const;
	
protected:
	void attachTexture(std::string);
	
private:
	Type type;
	Facing facing;
	
	float moving;
	
	sf::Vector2f rawPosition;
};

#endif