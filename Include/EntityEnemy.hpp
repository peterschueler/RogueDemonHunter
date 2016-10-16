#ifndef ENTITYENEMY_HPP
#define ENTITYENEMY_HPP

#include "Entity.hpp"

#include <string>

class EntityEnemy : public Entity {
public:
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
public:
	EntityEnemy();
	// x, y, type
	EntityEnemy(int, int, int);
	void update(sf::Time);
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
	EntityEnemy::Type getType() const { return type; }
	
	void walk();
	
protected:
	void attachTexture(std::string);
	
private:
	void animate();
	void flip();
	float valley_y;
	int stepsTaken;
	int maxSteps;
	
	enum Direction {
		up,
		down,
		left,
		right
	};
	Direction walkingDirection;

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