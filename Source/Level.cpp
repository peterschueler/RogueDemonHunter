#include "../Include/Level.hpp"

#include <iostream>

Level::Level(std::string path) {
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
			wall->setDirection(0,2);
		}
	}
}

void Level::moveToLevel(unsigned int lvl) {
	
}