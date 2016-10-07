#include "../Include/EntityHeroine.hpp"

#include <iostream>

EntityHeroine::EntityHeroine() {
	attachTexture("Assets/Textures/Heroine_Sheet_01.png");
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void EntityHeroine::attachTexture(std::string path) {
	sf::IntRect rect = sf::IntRect(0,0,8,8);
	if (texture.loadFromFile(path)) {
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
	} else {
		std::cerr << "ERROR! Couldn't load texture!" << std::endl;
	}
}

void EntityHeroine::update(sf::Time delta) {
	move(direction * delta.asSeconds());
}

void EntityHeroine::setDirection(float vx, float vy) {
	if (vx > 0) {
		walkingDirection = right;
	} else if (vx < 0) {
		walkingDirection = left;
	} else if (vy < 0) {
		walkingDirection = up;
	} else if (vy > 0) {
		walkingDirection = down;
	}
	direction.x = vx;
	direction.y = vy;
	animate();
}

sf::Vector2f EntityHeroine::getDirection() const {
	return direction;
}

void EntityHeroine::animate() {
	if (walkingDirection == right) {
		if (currentStep > third_x_pos) {
			currentStep = first_x_pos;
		}
		if (currentStep == first_x_pos) {
			sf::IntRect rect(0,16,8,8);
			sprite.setTextureRect(rect);
			currentStep = second_x_pos;
		} else if (currentStep == second_x_pos) {
			sf::IntRect rect(8,16,8,8);
			sprite.setTextureRect(rect);
			currentStep = third_x_pos;
		} else if (currentStep == third_x_pos) {
			sf::IntRect rect(16,16,8,8);
			sprite.setTextureRect(rect);
			currentStep = first_x_pos;
		}
	} else if (walkingDirection == left) {
		if (currentStep > third_x_neg || currentStep < first_x_neg) {
			currentStep = first_x_neg;
		}
		if (currentStep == first_x_neg) {
			sf::IntRect rect(0,24,8,8);
			sprite.setTextureRect(rect);
			currentStep = second_x_neg;
		} else if (currentStep == second_x_neg) {
			sf::IntRect rect(8,24,8,8);
			sprite.setTextureRect(rect);
			currentStep = third_x_neg;
		} else if (currentStep == third_x_neg) {
			sf::IntRect rect(16,24,8,8);
			sprite.setTextureRect(rect);
			currentStep = first_x_neg;
		}
	} else if (walkingDirection == down) {
		if (currentStep > third_y_pos || currentStep < first_y_pos) {
			currentStep = first_y_pos;
		}
		if (currentStep == first_y_pos) {
			sf::IntRect rect(0,0,8,8);
			sprite.setTextureRect(rect);
			currentStep = second_y_pos;
		} else if (currentStep == second_y_pos) {
			sf::IntRect rect(8,0,8,8);
			sprite.setTextureRect(rect);
			currentStep = third_y_pos;
		} else if (currentStep == third_y_pos) {
			sf::IntRect rect(16,0,8,8);
			sprite.setTextureRect(rect);
			currentStep = first_y_pos;
		}
	} else if (walkingDirection == up) {
		if (currentStep < first_y_neg) {
			currentStep = first_y_neg;
		}
		if (currentStep == first_y_neg) {
			sf::IntRect rect(0,8,8,8);
			sprite.setTextureRect(rect);
			currentStep = second_y_neg;
		} else if (currentStep == second_y_neg) {
			sf::IntRect rect(8,8,8,8);
			sprite.setTextureRect(rect);
			currentStep = third_y_neg;
		} else if (currentStep == third_y_neg) {
			sf::IntRect rect(16,8,8,8);
			sprite.setTextureRect(rect);
			currentStep = first_y_neg;
		}
	}
}