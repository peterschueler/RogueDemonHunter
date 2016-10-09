#include "../Include/FileManager.hpp"

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<std::string> split_str(const std::string& string, char delimeter) {
	std::vector<std::string> data;
	std::stringstream stream(string);
	std::string value;
	while (getline(stream, value, delimeter)) {
		data.push_back(value);
	}
	return data;
}

FileLevel FileManager::loadLevel(const std::string& levelName) {
	FileLevel lvl;
	lvl.name = levelName;
	std::string path = levelName + ".lvl";
	std::vector<std::string> lines = FileManager::parseFile(path);
	
	std::vector<std::vector<std::string> > cutLines;
	
	std::vector<std::string> wallLines;
	std::vector<std::string> enemyLines;
	std::vector<std::string> buttonLines;
	std::vector<std::string> doorLines;
	
	// 1. Split at '=' to ascertain type
	for (auto line : lines) {
		if (line[0] == '#') {
			continue;
		} else {
			std::vector<std::string> strs;
			for (auto vec : split_str(line, '=')) {
				strs.push_back(vec);
			}
			cutLines.push_back(strs);
		}
	}
	
	// 2. Sort data from type into right track
	for (auto line : cutLines) {
		if (line.front() == "door") {
			doorLines.push_back(line.back());
		} else if (line.front() == "enemy") {
			enemyLines.push_back(line.back());
		} else if (line.front() == "button") {
			buttonLines.push_back(line.back());
		} else if (line.front() == "wall") {
			wallLines.push_back(line.back());
		}
	}
	
	// 3. cut lines for further processing
	auto lineCutter = [](std::vector<std::string> lines) {
		std::vector<std::vector<std::string> > cutLines;
		for (auto line : lines) {
			std::vector<std::string> strs;
			for (auto vec : split_str(line, ' ')) {
				strs.push_back(vec);
			}
			cutLines.push_back(strs);
		}
		return cutLines;
	};
	
	auto cutWalls = lineCutter(wallLines); 
	auto cutDoors = lineCutter(doorLines);
	auto cutEnemies = lineCutter(enemyLines);
	auto cutButtons = lineCutter(buttonLines);
	
	// 4. create objects from read lines
	auto prepareObject = [](std::vector<std::vector<std::string> > lines) {
	};
	
	for (auto line : cutWalls) {
		WallObject nextObject;
		
		for (auto iter = line.begin(); iter != line.end(); ++iter) {
			std::vector<std::string> str = split_str(*iter, ':');
			if (str.front() == "x") {
				nextObject.x = std::stoi(str.back());
			} else if (str.front() == "y") {
				nextObject.y = std::stoi(str.back());
			} else if (str.front() == "t") {
				nextObject.type = std::stoi(str.back());
			}
		}
		lvl.walls.push_back(nextObject);
	}
	for (auto line : cutEnemies) {
		EnemyObject nextObject;
		
		for (auto iter = line.begin(); iter != line.end(); ++iter) {
			std::vector<std::string> str = split_str(*iter, ':');
			if (str.front() == "x") {
				nextObject.x = std::stoi(str.back());
			} else if (str.front() == "y") {
				nextObject.y = std::stoi(str.back());
			} else if (str.front() == "t") {
				nextObject.type = std::stoi(str.back());
			}
		}
		lvl.enemies.push_back(nextObject);
	}
	for (auto line : cutButtons) {
		ButtonObject nextObject;
		
		for (auto iter = line.begin(); iter != line.end(); ++iter) {
			std::vector<std::string> str = split_str(*iter, ':');
			if (str.front() == "x") {
				nextObject.x = std::stoi(str.back());
			} else if (str.front() == "y") {
				nextObject.y = std::stoi(str.back());
			} else if (str.front() == "t") {
				nextObject.type = std::stoi(str.back());
			}
		}
		lvl.buttons.push_back(nextObject);
	}
	for (auto line : cutDoors) {
		DoorObject nextObject;
		
		for (auto iter = line.begin(); iter != line.end(); ++iter) {
			std::vector<std::string> str = split_str(*iter, ':');
			if (str.front() == "x") {
				nextObject.x = std::stoi(str.back());
			} else if (str.front() == "y") {
				nextObject.y = std::stoi(str.back());
			} else if (str.front() == "t") {
				nextObject.type = std::stoi(str.back());
			}
		}
		lvl.doors.push_back(nextObject);
	}
	return lvl;
}

bool FileManager::saveLevel(const FileLevel& level) {
	std::string path = level.name + ".lvl";
	std::cout << path << std::endl;
	std::ofstream levelFile(path);
	for (auto wall : level.walls) {
		std::string output = std::string("x:") + std::to_string(wall.x) + std::string(" y:") + std::to_string(wall.y) + std::string(" type:") + std::to_string(wall.type) + "\n";
		levelFile << output;
	}
}

void FileManager::loadSettings(const std::string&) {
}

bool FileManager::saveSettings(const Settings&) {
}

std::vector<std::string> FileManager::parseFile(const std::string& path) {
	std::cout << "SELECTED FILE: " << path << std::endl;
	std::vector<std::string> lines;
	std::string current;
	std::ifstream file(path);
	if (file.is_open()) {
		while (getline(file, current)) {
			lines.push_back(current);
		}
		file.close();
	} else {
		std::cerr << "Unable to open file!";
	}
	return lines;	
}