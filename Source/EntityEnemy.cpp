#include "../Include/EntityEnemy.hpp"

#include <iostream>

EntityEnemy::EntityEnemy() {
	attachTexture("Assets/Textures/Monsters_Sheet_01.png");
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

EntityEnemy::EntityEnemy(int _x, int _y, int _type): type(EntityEnemy::Type(_type)) {
	setPosition(sf::Vector2f(_x, _y));
	attachTexture("Assets/Textures/Monsters_Sheet_01.png");
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
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
	if (vx > 0) {
		walkingDirection = right;
	} else if (vx < 0) {
		walkingDirection = left;
	} else if (vy > 0) {
		walkingDirection = down;
	} else if (vy < 0) {
		walkingDirection = up;
	}
	direction.x = vx;
	direction.y = vy;
	animate();
}

sf::Vector2f EntityEnemy::getDirection() const {
	return direction;
}

void EntityEnemy::animate() {
	switch (type) {
		case ghoul:
			if (walkingDirection == up) {
				if (currentStep == back_first) {
					sf::IntRect rect(0,0,8,16);
					sprite.setTextureRect(rect);
					currentStep = back_second;
				} else if (currentStep == back_second) {
					sf::IntRect rect(0,8,8,16);
					sprite.setTextureRect(rect);
					currentStep = back_first;
				}
		} else if (walkingDirection == down) {
			if (currentStep == front_first) {
				sf::IntRect rect(8,0,8,16);
				sprite.setTextureRect(rect);
				currentStep = front_second;
			} else if (currentStep == front_second) {
				sf::IntRect rect(8,8,8,16);
				sprite.setTextureRect(rect);
				currentStep = front_first;
		}
		}
		break;
	case dinosaur:
		if (walkingDirection == left) {	
			sprite.setScale({-1,1});
			if (currentStep == left_first) {
				sf::IntRect rect(16,0,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_second;
			} else if (currentStep == left_second) {
				sf::IntRect rect(16,8,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_first;
			}
		} else if (walkingDirection == right) {
			sprite.setScale({-1,1});
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
			sprite.setScale({-1,1});
			if (currentStep == left_first) {
				sf::IntRect rect(16,16,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_second;
			} else if (currentStep == left_second) {
				sf::IntRect rect(16,24,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_first;
			}
		} else if (walkingDirection == right) {
			sprite.setScale({-1,1});
			if (currentStep == right_first) {
				sf::IntRect rect(16,16,16,8);
				sprite.setTextureRect(rect);
				currentStep = right_second;
			} else if (currentStep == right_second) {
				sf::IntRect rect(16,24,16,8);
				sprite.setTextureRect(rect);
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
			sprite.setScale({-1,1});
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
			sprite.setScale({-1,1});
			if (currentStep == left_first) {
				sf::IntRect rect(32,16,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_second;
			} else if (currentStep == left_second) {
				sf::IntRect rect(40,16,16,8);
				sprite.setTextureRect(rect);
				currentStep = left_first;
			}
		} else if (walkingDirection == right) {
			sprite.setScale({-1,1});
			if (currentStep == right_first) {
				sf::IntRect rect(32,16,16,8);
				sprite.setTextureRect(rect);
				currentStep = right_second;
			} else if (currentStep == right_second) {
				sf::IntRect rect(40,16,16,8);
				sprite.setTextureRect(rect);
				currentStep = right_first;
			}
		}
		break;
	case floatingHead:
		if (walkingDirection == left) {	
			sprite.setScale({-1,1});
			if (currentStep == left_first) {
				sf::IntRect rect(48,0,8,8);
				sprite.setTextureRect(rect);
				currentStep = left_second;
			} else if (currentStep == left_second) {
				sf::IntRect rect(56,0,8,8);
				sprite.setTextureRect(rect);
				currentStep = left_first;
			}
		} else if (walkingDirection == right) {
			sprite.setScale({-1,1});
			if (currentStep == right_first) {
				sf::IntRect rect(48,0,8,8);
				sprite.setTextureRect(rect);
				currentStep = right_second;
			} else if (currentStep == right_second) {
				sf::IntRect rect(56,0,8,8);
				sprite.setTextureRect(rect);
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