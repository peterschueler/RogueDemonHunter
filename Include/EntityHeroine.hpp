#ifndef ENTITYHEROINE_HPP
#define ENTITYHEROINE_HPP

#include "Entity.hpp"

#include <string>

class EntityHeroine : public Entity {
public:
	enum Direction {
		left, right, up, down
	};
public:
	EntityHeroine();
	void update(sf::Time);
	
	void setDirection(float, float);
	sf::Vector2f getDirection() const;
	
protected:
	void attachTexture(std::string);
	
private:
	enum AnimationStep {
		first_x_pos,
		second_x_pos,
		third_x_pos,
		first_x_neg,
		second_x_neg,
		third_x_neg,
		first_y_pos,
		second_y_pos,
		third_y_pos,
		first_y_neg,
		second_y_neg,
		third_y_neg
	};
	AnimationStep currentStep;
	Direction walkingDirection;
	
	void animate();
};

#endif