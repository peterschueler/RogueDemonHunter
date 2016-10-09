#include "../Include/EntityEnemy.hpp"

#include <iostream>
#include <random>

EntityEnemy::EntityEnemy() {
	attachTexture("Assets/Textures/Monsters_Sheet_01.png");
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

EntityEnemy::EntityEnemy(int _x, int _y, int _type): type(EntityEnemy::Type(_type)), stepsTaken(0) {
	setPosition(sf::Vector2f(_x, _y));
	attachTexture("Assets/Textures/Monsters_Sheet_01.png");
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	
	// Randomized floating head behavior
	// http://stackoverflow.com/a/19728404
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0,4);
	valley_y = uni(rng);
	
	std::uniform_int_distribution<int> randomizer_dino(10,20);
	std::uniform_int_distribution<int> randomizer_rat(2,4);
	
	if (type == ghoul) { walkingDirection = down; maxSteps = 24; }
	if (type == dinosaur) { walkingDirection = left; maxSteps = randomizer_dino(rng); }
	if (type == rat) { walkingDirection = right; maxSteps = randomizer_rat(rng); }
	if (type == eye) { walkingDirection = left; maxSteps = 8; }
	if (type == floatingHead) { walkingDirection = left; maxSteps = 6; }
}

void EntityEnemy::attachTexture(std::string path) {
	sf::IntRect rect;
	if (type == ghoul) {
		rect = sf::IntRect(8,8,8,16);
	} else if (type == dinosaur) {
		rect = sf::IntRect(16,8,16,8);
	}else if (type == rat) {
		rect = sf::IntRect(16,16,16,8);
	} else if (type == pig) {
		rect = sf::IntRect(32,0,16,8);
	}else if (type == eye) {
		rect = sf::IntRect(32,16,8,8);
	} else if (type == floatingHead) {
		rect = sf::IntRect(48,0,8,8);
	} else if (type == vampire) {
		rect = sf::IntRect(48,8,8,8);
	} else if (type == undefined) {
		rect = sf::IntRect(40,24,8,8);
	}
	if (texture.loadFromFile(path)) {
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
	} else {
		std::cerr << "ERROR! Couldn't load texture!" << std::endl;
	}
}

void EntityEnemy::update(sf::Time delta) {
	move(direction * delta.asSeconds());
}

void EntityEnemy::setDirection(float vx, float vy) {
	direction.x = vx;
	direction.y = vy;
	animate();
}

sf::Vector2f EntityEnemy::getDirection() const {
	return direction;
}

void EntityEnemy::walk() {
	stepsTaken++;
	if (stepsTaken == maxSteps) {
		flip();
		stepsTaken = 0;
	}
	switch (type) {
		case ghoul:
			if (walkingDirection == up) {
				setDirection(0, 2);
			} else if (walkingDirection == down) {
				setDirection(0, -2);
			}
			break;
		case dinosaur:
			if (walkingDirection == left) {
				setDirection(-7, 0);
			} else if (walkingDirection == right) {
				setDirection(7, 0);
			}
			break;
		case rat:
			if (walkingDirection == left) {
				setDirection(-11, 0);
			} else if (walkingDirection == right) {
				setDirection(11, 0);
			}
			break;
		case pig:
			break;
		case eye:
			if (walkingDirection == left) {
				if (valley_y > 2) {
					setDirection(-7, -5);
					valley_y = 1;
				} else {
					setDirection(-7, 5);
				}
				valley_y++;
			} else if (walkingDirection == right) {
				if (valley_y > 2) {
					setDirection(7, -5);
					valley_y = 1;
				} else {
					setDirection(7, 5);
				}
				valley_y++;
			}
			break;
		case floatingHead:
			if (valley_y == 0) {
				setDirection(-9, -5);
				valley_y = 1;
			} else if (valley_y == 1) {
				setDirection(-9, 5);
				valley_y = 2;
			} else if (valley_y == 2) {
				setDirection(9, 5);
				valley_y = 3;
			} else if (valley_y == 3) {
				setDirection(9, -5);
				valley_y = 0;
			} else {
				valley_y = 0;
			}
			break;
		case vampire:
			break;
		case undefined:
			break;
	}
}

void EntityEnemy::animate() {
	switch (type) {
		case ghoul:
			if (walkingDirection == up) {
				if (currentStep == front_first || currentStep == front_second) {
					currentStep = back_first;
				}
				if (currentStep == back_first) {
					sf::IntRect rect(8,0,8,16);
					sprite.setTextureRect(rect);
					currentStep = back_second;
				} else if (currentStep == back_second) {
					sf::IntRect rect(8,16,8,16);
					sprite.setTextureRect(rect);
					currentStep = back_first;
				} else {
					currentStep = back_first;
				}
		} else if (walkingDirection == down) {
			if (currentStep == back_first || currentStep == back_second) {
				currentStep = front_first;
			}
			if (currentStep == front_first) {
				sf::IntRect rect(0,0,8,16);
				sprite.setTextureRect(rect);
				currentStep = front_second;
			} else if (currentStep == front_second) {
				sf::IntRect rect(0,16,8,16);
				sprite.setTextureRect(rect);
				currentStep = front_first;
			} else { 
				currentStep = front_first;
			}
		}
		break;
	case dinosaur:
		if (walkingDirection == left) {	
			if (currentStep == right_first || currentStep == right_second) {
				currentStep = left_first;
			}
			sprite.setScale({-1,1});
			if (currentStep == left_first) {
				sf::IntRect rect(16,0,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_second;
			} else if (currentStep == left_second) {
				sf::IntRect rect(16,8,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_first;
			} else {
				currentStep = left_first;
			}
		} else if (walkingDirection == right) {
			if (currentStep == left_first || currentStep == left_second) {
				currentStep = right_first;
			}
			sprite.setScale({1,1});
			if (currentStep == right_first) {
				sf::IntRect rect(16,0,16,8);
				sprite.setTextureRect(rect);
				currentStep = right_second;
			} else if (currentStep == right_second) {
				sf::IntRect rect(16,8,16,8);
				sprite.setTextureRect(rect);
				currentStep = right_first;
			}
		}
		break;
	case rat:
		if (walkingDirection == left) {	
			if (currentStep == right_first || currentStep == right_second) {
				currentStep = left_first;
			}
			sprite.setScale({-1,1});
			if (currentStep == left_first) {
				sf::IntRect rect(16,16,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_second;
			} else if (currentStep == left_second) {
				sf::IntRect rect(16,24,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_first;
			} else {
				currentStep = left_first;
			}
		} else if (walkingDirection == right) {
			if (currentStep == left_first || currentStep == left_second) {
				currentStep = right_first;
			}
			sprite.setScale({1,1});
			if (currentStep == right_first) {
				sf::IntRect rect(16,16,16,8);
				sprite.setTextureRect(rect);
				currentStep = right_second;
			} else if (currentStep == right_second) {
				sf::IntRect rect(16,24,16,8);
				sprite.setTextureRect(rect);
				currentStep = right_first;
			} else {
				currentStep = right_first;
			}
		}
		break;
	case pig:
		if (walkingDirection == left) {	
			sprite.setScale({-1,1});
			if (currentStep == left_first) {
				sf::IntRect rect(32,0,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_second;
			} else if (currentStep == left_second) {
				sf::IntRect rect(32,8,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_first;
			}
		} else if (walkingDirection == right) {
			sprite.setScale({1,1});
			if (currentStep == right_first) {
				sf::IntRect rect(32,0,16,8);
				sprite.setTextureRect(rect);
				currentStep = right_second;
			} else if (currentStep == right_second) {
				sf::IntRect rect(32,8,16,8);
				sprite.setTextureRect(rect);
				currentStep = right_first;
			}
		}
		break;
	case eye: 
		if (walkingDirection == left) {	
			if (currentStep == right_first || currentStep == right_second) {
				currentStep = left_first;
			}
			sprite.setScale({-1,1});
			if (currentStep == left_first) {
				sf::IntRect rect(32,16,8,8);
				sprite.setTextureRect(rect);
				currentStep = left_second;
			} else if (currentStep == left_second) {
				sf::IntRect rect(40,16,8,8);
				sprite.setTextureRect(rect);
				currentStep = left_first;
			} else {
				currentStep = left_first;
			}
		} else if (walkingDirection == right) {
			if (currentStep == left_first || currentStep == left_second) {
				currentStep = right_first;
			}
			sprite.setScale({1,1});
			if (currentStep == right_first) {
				sf::IntRect rect(32,16,8,8);
				sprite.setTextureRect(rect);
				currentStep = right_second;
			} else if (currentStep == right_second) {
				sf::IntRect rect(40,16,8,8);
				sprite.setTextureRect(rect);
				currentStep = right_first;
			} else {
				currentStep = right_first;
			}
		}
		break;
	case floatingHead:
		if (walkingDirection == left) {	
			if (currentStep == right_first || currentStep == right_second) {
				currentStep = left_first;
			}
			sprite.setScale({-1,1});
			if (currentStep == left_first) {
				sf::IntRect rect(48,0,8,8);
				sprite.setTextureRect(rect);
				currentStep = left_second;
			} else if (currentStep == left_second) {
				sf::IntRect rect(56,0,8,8);
				sprite.setTextureRect(rect);
				currentStep = left_first;
			} else {
				currentStep = left_first;
			}
		} else if (walkingDirection == right) {
			if (currentStep == left_first || currentStep == left_second) {
				currentStep = right_first;
			}
			sprite.setScale({1,1});
			if (currentStep == right_first) {
				sf::IntRect rect(48,0,8,8);
				sprite.setTextureRect(rect);
				currentStep = right_second;
			} else if (currentStep == right_second) {
				sf::IntRect rect(56,0,8,8);
				sprite.setTextureRect(rect);
				currentStep = right_first;
			} else {
				currentStep = right_first;
			}
		}
		break;
	case vampire:
		if (walkingDirection == up) {
			if (currentStep == back_first) {
				sf::IntRect rect(48,8,8,16);
				sprite.setTextureRect(rect);
				currentStep = back_second;
			} else if (currentStep == back_second) {
				sf::IntRect rect(56,8,8,16);
				sprite.setTextureRect(rect);
				currentStep = back_first;
		}
		} else if (walkingDirection == down) {
			if (currentStep == front_first) {
				sf::IntRect rect(48,16,8,16);
				sprite.setTextureRect(rect);
				currentStep = front_second;
			} else if (currentStep == front_second) {
				sf::IntRect rect(56,16,8,16);
				sprite.setTextureRect(rect);
				currentStep = front_first;
			}
		}
		break;
	case undefined:
		if (walkingDirection == up) {	
			if (currentStep == left_first) {
				sf::IntRect rect(40,24,8,8);
				sprite.setTextureRect(rect);
				currentStep = left_second;
			} else if (currentStep == left_second) {
				sf::IntRect rect(48,24,8,8);
				sprite.setTextureRect(rect);
				currentStep = left_first;
			}
		} else if (walkingDirection == down) {
			if (currentStep == right_first) {
				sf::IntRect rect(40,24,8,8);
				sprite.setTextureRect(rect);
				currentStep = right_second;
			} else if (currentStep == right_second) {
				sf::IntRect rect(48,24,8,8);
				sprite.setTextureRect(rect);
				currentStep = right_first;
			}
		}
		break;
	};
}

void EntityEnemy::flip() {
	if (walkingDirection == left) {  walkingDirection = right; }
	else if (walkingDirection == right) {  walkingDirection = left; }
	else if (walkingDirection == up) { walkingDirection = down; }
	else if (walkingDirection == down) { walkingDirection = up; }
}