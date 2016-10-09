#include "../Include/Level.hpp"

#include <iostream>

Level::Level(unsigned int lvl) {
	std::string path = "Assets/Levels/" + std::to_string(lvl);
	// load level data from string path
	FileLevel currentLevel = FileManager::loadLevel(path);
	for (auto wall : currentLevel.walls) {
		EntityWall* newWall = new EntityWall(wall.x, wall.y, wall.type);
		walls.push_back(std::move(newWall));
	}
	for (auto enemy : currentLevel.enemies) {
		EntityEnemy* newEnemy = new EntityEnemy(enemy.x, enemy.y, enemy.type);
		enemies.push_back(std::move(newEnemy));
	}
	for (auto button : currentLevel.buttons) {
		EntityButton* newButton = new EntityButton(button.x, button.y, button.type);
		buttons.push_back(std::move(newButton));
	}
}

std::vector<EntityEnemy*> Level::getEnemies() {
	std::vector<EntityEnemy*> undeletedEnemies;
	for (auto enemy : enemies) {
		if (enemy->getDeleted() == false) {
			undeletedEnemies.push_back(enemy);
		}
	}
	return undeletedEnemies;
}

std::vector<EntityWall*> Level::getWalls() const {
	std::vector<EntityWall*> undeletedWalls;
	for (auto wall : walls) {
		if (wall->getDeleted() == false) {
			undeletedWalls.push_back(wall);
		}
	}
	return undeletedWalls;
}

std::vector<EntityButton*> Level::getButtons() {
	std::vector<EntityButton*> undeletedButtons;
	for (auto button : buttons) {
		if (button->getDeleted() == false) {
			undeletedButtons.push_back(button);
		}
	}
	return undeletedButtons;
}

void Level::openDoors() {
	for (auto wall : getWalls()) {
		if (wall->getType() == EntityWall::Type::outer_door) {
			if (wall->getFacing() == EntityWall::Facing::north) {
				wall->setDirection(0,-2);
			} else if (wall->getFacing() == EntityWall::Facing::south) {
				wall->setDirection(0,2);
			} else if (wall->getFacing() == EntityWall::Facing::west) {
				wall->setDirection(-2,0);
			} else if (wall->getFacing() == EntityWall::Facing::east) {
				wall->setDirection(2,0);
			}
		}
	}
}

void Level::closeWalls() {
	for (auto wall : getWalls()) {
		if (wall->getType() == EntityWall::Type::outer_second) {
			if (wall->getFacing() == EntityWall::Facing::south) {
				wall->setDirection(2,0);
			} else if (wall->getFacing() == EntityWall::Facing::north) {
				wall->setDirection(-2,0);
			} else if (wall->getFacing() == EntityWall::Facing::west) {
				wall->setDirection(0, -2);
			} else if (wall->getFacing() == EntityWall::Facing::east) {
				wall->setDirection(0, 2);
			}
		} else if (wall->getType() == EntityWall::Type::outer_third) {
			if (wall->getFacing() == EntityWall::Facing::south) {
				wall->setDirection(-2,0);
			} else if (wall->getFacing() == EntityWall::Facing::north) {
				wall->setDirection(2,0);
			} else if (wall->getFacing() == EntityWall::Facing::west) {
				wall->setDirection(0, 2);
			} else if (wall->getFacing() == EntityWall::Facing::east) {
				wall->setDirection(0, -2);
			}
		}
	}
}

void Level::clearRoom() {
	enemies.clear();
	buttons.clear();
}

bool Level::moveToLevel(unsigned int lvl) {
	std::string path = "Assets/Levels/" + std::to_string(lvl);
	FileLevel level = FileManager::loadLevel(path);
	// 3. set new door
	for (auto wall : walls) {
		for (auto door : level.walls) {
			if (wall->getRawPosition().x == door.x && wall->getRawPosition().y == door.y) {
				if (door.type == 1) {
					walls.push_back(new EntityWall(door.x, door.y, door.type));
				} else {
					wall->setType(EntityWall::Type(door.type));
				}
			}
		}
	}
	// 4. add new enemies
	for (auto enemy : level.enemies) {
		EntityEnemy* newEnemy = new EntityEnemy(enemy.x, enemy.y, enemy.type);
		enemies.push_back(std::move(newEnemy));
	}
	// 5. add new buttons
	for (auto button : level.buttons) {
		EntityButton* newButton = new EntityButton(button.x, button.y, button.type);
		buttons.push_back(std::move(newButton));
	}
	// 6. restart 
	return true;
}