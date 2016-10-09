#include "../Include/EntityWall.hpp"

#include <iostream>

EntityWall::EntityWall() {
	attachTexture("Assets/Textures/Walls_Sheet_01.png");
}

EntityWall::EntityWall(int _x, int _y, int _type): type(EntityWall::Type(_type)), moving(0) {
	setPosition(sf::Vector2f(_x, _y));
	rawPosition = sf::Vector2f(_x, _y);
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
			facing = north;
		} else if (_y == 136) {
			sprite.rotate(270.f);
			setPosition({static_cast<float>(_x), static_cast<float>(_y + 8)});
			facing = south;
		} 
		if (_x == 144) {
			sprite.rotate(180.f);
			setPosition({static_cast<float>(_x + 16), static_cast<float>(getPosition().y + 8)});
			facing = east;
		} else if (_x == 0) {
			facing = west;
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
	auto maxMove = 0;
	if (type == EntityWall::outer_door) {
		maxMove = 36;
	} else if (type == EntityWall::outer_second) {
		maxMove = 24;
	} else if (type == EntityWall::outer_third) {
		maxMove = 24;
	}
	if (direction.x != 0) {
		moving += 0.1;
		if (moving < maxMove) {
			move(direction * delta.asSeconds());
		} else {
			if (type == EntityWall::outer_door) { setDeleted(true); }
			if (type == EntityWall::outer_third || type == EntityWall:: outer_second) { setType(outer_first); }
			direction.x = 0;
			moving = 0;
		}
	}
	if (direction.y != 0) {
		moving += 0.1;
		if (moving < maxMove) {
			move(direction * delta.asSeconds());
		} else {
			if (type == EntityWall::outer_door) { setDeleted(true); }
			if (type == EntityWall::outer_third || type == EntityWall:: outer_second) { setType(outer_first); }
			direction.y = 0;
			moving = 0;
		}
	}
}

void EntityWall::setDirection(float vx, float vy) {
	direction.x = vx;
	direction.y = vy;
}

sf::Vector2f EntityWall::getDirection() const {
	return direction;
}

void EntityWall::setType(EntityWall::Type _type) {
	type = _type;
			if (rawPosition.y == 0) {
			facing = north;
		} else if (rawPosition.y == 136) {
			facing = south;
		} 
		if (rawPosition.x == 144) {
			facing = east;
		} else if (rawPosition.x == 0) {
			facing = west;
		}
	attachTexture("Assets/Textures/Walls_Sheet_01.png");
}

EntityWall::Type EntityWall::getType() const {
	return type;
}

EntityWall::Facing EntityWall::getFacing() const {
	return facing;
}

sf::Vector2f EntityWall::getRawPosition() const {
	return rawPosition;
}