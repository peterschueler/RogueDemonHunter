#include "../Include/EntityWall.hpp"

#include <iostream>

EntityWall::EntityWall() {
	attachTexture("Assets/Textures/Walls_Sheet_01.png");
}

EntityWall::EntityWall(int _x, int _y, int _type): type(EntityWall::Type(_type)) {
	setPosition(sf::Vector2f(_x, _y));
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	
	attachTexture("Assets/Textures/Walls_Sheet_01.png");
	
	if (type == outer_first) {
		if (_y == 0) {
			sprite.rotate(90.f);
			setPosition({static_cast<float>(_x + 8), static_cast<float>(_y)});
		} else if (_y == 136) {
			sprite.rotate(270.f);
			setPosition({static_cast<float>(_x), static_cast<float>(_y + 8)});
		}
		if (_x == 144) {
			sprite.rotate(180.f);
			setPosition({static_cast<float>(_x + 16), static_cast<float>(getPosition().y + 8)});
		}
	} else if (type == outer_second) {
		if (_y == 0) {
			sprite.rotate(90.f);
			setPosition({static_cast<float>(_x + 8), static_cast<float>(_y)});
		} else if (_y == 136) {
			sprite.rotate(270.f);
			setPosition({static_cast<float>(_x), static_cast<float>(_y + 8)});
		}
		if (_x == 144) {
			sprite.rotate(180.f);
			setPosition({static_cast<float>(_x + 16), static_cast<float>(getPosition().y + 8)});
		}
	} else if (type == outer_third) {
		if (_y == 0) {
			sprite.rotate(90.f);
			setPosition({static_cast<float>(_x + 8), static_cast<float>(_y)});
		} else if (_y == 136) {
			sprite.rotate(270.f);
			setPosition({static_cast<float>(_x), static_cast<float>(_y + 8)});
		}
		if (_x == 144) {
			sprite.rotate(180.f);
			setPosition({static_cast<float>(_x + 16), static_cast<float>(getPosition().y + 8)});
		}
	} else if (type == outer_corner) {
		if (_x == 144) {
			if (_y == 0) {
				sprite.rotate(90.f);
				setPosition({static_cast<float>(_x + 16), static_cast<float>(_y)});
			} else {
				sprite.rotate(180.f);
				setPosition({static_cast<float>(_x + 16), static_cast<float>(_y + 8)});
			}
		} else if (_x == 0) {
			if (_y == 136) {
				sprite.rotate(270.f);
				setPosition({static_cast<float>(_x), static_cast<float>(_y + 8)});
			}
		}
	} else if (type == outer_door) {
		if (_y == 0) {
				sprite.rotate(90.f);
				setPosition({static_cast<float>(_x + 8), static_cast<float>(_y)});
			} else if (_y == 136) {
				sprite.rotate(270.f);
				setPosition({static_cast<float>(_x), static_cast<float>(_y + 8)});
			}
			if (_x == 144) {
				sprite.rotate(180.f);
				setPosition({static_cast<float>(_x + 16), static_cast<float>(getPosition().y + 8)});
			}
	}
}

void EntityWall::attachTexture(std::string path) {
	sf::IntRect rect;
	if (type == outer_corner) {
		rect = sf::IntRect(0,0,16,16);
	} else if (type == outer_first) {
		rect = sf::IntRect(32,0,16,8);
	} else if (type == outer_second) {
		rect = sf::IntRect(16,8,16,8); 
	} else if (type == outer_third) {
		rect = sf::IntRect(16,0,16,8);
	} else if (type == outer_door) {
		rect = sf::IntRect(32,8,16,8);
	}
	if (texture.loadFromFile(path)) {
		sprite.setTexture(texture);
		sprite.setTextureRect(rect);
	} else {
		std::cerr << "ERROR! Couldn't load texture!" << std::endl;
	}
}

void EntityWall::update(sf::Time delta) {
	move(direction * delta.asSeconds());
}

void EntityWall::setDirection(float vx, float vy) {
	direction.x = vx;
	direction.y = vy;
}

sf::Vector2f EntityWall::getDirection() const {
	return direction;
}