#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

struct Object {
};

struct WallObject {
	int x, y;
	int type;
	
	WallObject() {
	}
	
	WallObject(int _x, int _y, int _type): x(_x), y(_y), type(_type) {
	}
};

struct DoorObject {
	int x, y;
	int type;
	
	DoorObject() {
	}
	
	DoorObject(int _x, int _y, int _type): x(_x), y(_y), type(_type) {
	}
};

struct EnemyObject {
	int x, y;
	int type;
	
	EnemyObject() {
	}
	
	EnemyObject(int _x, int _y, int _type): x(_x), y(_y), type(_type) {
	}
};

struct ButtonObject {
	int x, y;
	int type;
	
	ButtonObject() {
	}
	
	ButtonObject(int _x, int _y, int _type): x(_x), y(_y), type(_type) {
	}
};

struct Level {
	std::vector<WallObject> walls;
	std::vector<EnemyObject> enemies;
	std::vector<ButtonObject> buttons;
	std::vector<DoorObject> doors;
	
	std::string name;
	
	Level(): walls(), enemies(), buttons(), name() {
	}
	
	Level(const std::string& lvl, std::vector<WallObject> _walls): walls(_walls), enemies(), buttons(), name(lvl) {
	}
};

#endif