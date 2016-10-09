#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <string>

#include "Entities.hpp"
#include "FileManager.hpp"

class Level {
public:
	Level(unsigned int);
	
	std::vector<EntityEnemy*> getEnemies();
	std::vector<EntityWall*> getWalls() const;
	std::vector<EntityButton*> getButtons();
	
	void openDoors();
	void closeWalls();
	void clearRoom();
	bool moveToLevel(unsigned int);
	
private:
	std::vector <EntityEnemy*> enemies;
	std::vector <EntityWall*> walls;
	std::vector <EntityButton*> buttons;
};

#endif