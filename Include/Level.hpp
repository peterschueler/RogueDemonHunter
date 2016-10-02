#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <vector>

struct BlockObject {
	int x, y;
	int type;
	
	BlockObject() {
	}
	
	BlockObject(int _x, int _y, int _type) {
		x = _x;
		y = _y;
		type = _type;
	}
};

struct Level {
	std::vector<BlockObject> blocks;
	std::string name;
	
	Level() {
	}
	
	Level(const std::string& lvl, std::vector<BlockObject> blcks) {
		name = lvl;
		blocks = blcks;
	}
};

#endif