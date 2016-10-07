#include "../Include/Level.hpp"

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
	return enemies;
}

std::vector<EntityWall*> Level::getWalls() const {
	return walls;
}

std::vector<EntityButton*> Level::getButtons() {
	return buttons;
}