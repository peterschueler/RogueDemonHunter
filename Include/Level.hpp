#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>

#include "Entities.hpp"
#include "FileManager.hpp"

class Level {
public:
	Level(std::string);
	
	std::vector<EntityEnemy*> getEnemies();
	std::vector<EntityWall*> getWalls() const;
	std::vector<EntityButton*> getButtons();
	
private:
	std::vector <EntityEnemy*> enemies;
	std::vector <EntityWall*> walls;
	std::vector <EntityButton*> buttons;
};

#endif