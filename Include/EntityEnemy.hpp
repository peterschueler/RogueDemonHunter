#ifndef ENTITYENEMY_HPP
#define ENTITYENEMY_HPP

#include "Entity.hpp"

#include <string>

class EntityEnemy : public Entity {
public:
	EntityEnemy();
	// x, y, type
	EntityEnemy(int, int, int);
	void update(sf::Time);
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
protected:
	void attachTexture(std::string);
	
private:
	void animate();
	
	enum Direction {
		up,
		down,
		left,
		right
	};
	Direction walkingDirection;
	
	enum Type {
		ghoul,
		dinosaur,
		rat,
		pig,
		eye,
		floatingHead,
		vampire,
		undefined
	};
	Type type;
	
	enum AnimationStep {
		front_first,
		front_second,
		back_first,
		back_second,
		left_first,
		left_second,
		right_first,
		right_second
	};
	AnimationStep currentStep;
};

#endif