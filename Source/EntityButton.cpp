#include "../Include/EntityButton.hpp"

#include <iostream>

EntityButton::EntityButton() {
	attachTexture("Assets/Textures/Buttons_Sheet_01.png");
}

EntityButton::EntityButton(int _x, int _y, int _type): type(EntityButton::Type(_type)) {
	attachTexture("Assets/Textures/Buttons_Sheet_01.png");
	setPosition(_x, _y);
}

void EntityButton::attachTexture(std::string path) {
	sf::IntRect rect;
	if (type == doorKey) {
		rect = sf::IntRect(0,0,16,8);	
	} else if (type == healthPod) {
		rect = sf::IntRect(0,8,8,8);
	} else if (type == pausePod) {
		rect = sf::IntRect(8,8,8,8);
	}
	if (texture.loadFromFile(path)) {
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
	} else {
		std::cerr << "ERROR! Couldn't load texture!" << std::endl;
	}
}

void EntityButton::update(sf::Time delta) {
	move(direction * delta.asSeconds());
}

void EntityButton::setDirection(float vx, float vy) {
	direction.x = vx;
	direction.y = vy;
}

sf::Vector2f EntityButton::getDirection() const {
	return direction;
}