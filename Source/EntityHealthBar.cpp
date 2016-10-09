#include "../Include/EntityHealthBar.hpp"

#include <iostream>

EntityHealthBar::EntityHealthBar(): health(4) {
	attachTexture("Assets/Textures/Healthbar_01.png");
	std::string heartPath = "Assets/Textures/Health_Sheet_01.png";
	sf::IntRect rect = sf::IntRect(0,8,8,8);
	if (heartTexture.loadFromFile(heartPath)) {
		heartOne.setTexture(heartTexture);
		heartOne.setTextureRect(rect);
		heartTwo.setTexture(heartTexture);
		heartTwo.setTextureRect(rect);
		heartThree.setTexture(heartTexture);
		heartThree.setTextureRect(rect);
		heartFour.setTexture(heartTexture);
		heartFour.setTextureRect(rect);
	} else {
		std::cerr << "ERROR! Couldn't load heart texture!" << std::endl;
	}
	heartOne.setPosition(112,-1);
	heartTwo.setPosition(120,-1);
	heartThree.setPosition(128,-1);
	heartFour.setPosition(136,-1);

	
}

void EntityHealthBar::attachTexture(std::string path) {
	sf::IntRect rect = sf::IntRect(0,0,160,8);
	if (texture.loadFromFile(path)) {
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
	} else {
		std::cerr << "ERROR! Couldn't load texture!" << std::endl;
	}
}

void EntityHealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
	
	target.draw(heartOne, states);
	target.draw(heartTwo, states);
	target.draw(heartThree, states);
	target.draw(heartFour, states);
}

void EntityHealthBar::update(sf::Time delta) {
	sf::IntRect fullRect = sf::IntRect(0,8,8,8);
	sf::IntRect emptyRect = sf::IntRect(0,0,8,8);
	if (health == 4) {
		heartOne.setTextureRect(fullRect);
		heartTwo.setTextureRect(fullRect);
		heartThree.setTextureRect(fullRect);
		heartFour.setTextureRect(fullRect);
	} else if (health == 3) {
		heartOne.setTextureRect(fullRect);
		heartTwo.setTextureRect(fullRect);
		heartThree.setTextureRect(fullRect);
		heartFour.setTextureRect(emptyRect);
	} else if (health == 2) {
		heartOne.setTextureRect(fullRect);
		heartTwo.setTextureRect(fullRect);
		heartThree.setTextureRect(emptyRect);
		heartFour.setTextureRect(emptyRect);		
	} else if (health == 1) {
		heartOne.setTextureRect(fullRect);
		heartTwo.setTextureRect(emptyRect);
		heartThree.setTextureRect(emptyRect);
		heartFour.setTextureRect(emptyRect);		
	} else if (health == 0) {
		heartOne.setTextureRect(emptyRect);
		heartTwo.setTextureRect(emptyRect);
		heartThree.setTextureRect(emptyRect);
		heartFour.setTextureRect(emptyRect);
	}
}

void EntityHealthBar::setDirection(float vx, float vy) {
	direction.x = vx;
	direction.y = vy;
}

sf::Vector2f EntityHealthBar::getDirection() const {
	return direction;
}

void EntityHealthBar::setColor(sf::Color col) {
	sprite.setColor(col);
	heartOne.setColor(col);
	heartTwo.setColor(col);
	heartThree.setColor(col);
	heartFour.setColor(col);
}

void EntityHealthBar::setHealth(unsigned int heal) {
	std::cout << "Called setHealth with: " << heal << std::endl;
	health = heal;
}