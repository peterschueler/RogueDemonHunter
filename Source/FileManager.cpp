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

Level FileManager::loadLevel(const std::string& levelName) {
	Level lvl;
	lvl.name = levelName;
	std::string path = levelName + ".lvl";
	std::vector<std::string> lines = FileManager::parseFile(path);
	
	for (auto line : lines) { std::cout << line << std::endl; }
	
	std::vector<std::vector<std::string> > cutLines;
	for (auto line : lines) {
		std::vector<std::string> strs;
		for (auto vec : split_str(line, ' ')) {
			strs.push_back(vec);
		}
		cutLines.push_back(strs);
	}
	
	for (auto line : cutLines) {
		BlockObject nextObject;
		
		for (auto iter = line.begin(); iter != line.end(); ++iter) {
			std::vector<std::string> str = split_str(*iter, ':');
			if (str.front() == "x") {
				nextObject.x = std::stoi(str.back());
			} else if (str.front() == "y") {
				nextObject.y = std::stoi(str.back());
			} else if (str.front() == "type") {
				nextObject.type = std::stoi(str.back());
			}
		}
		lvl.blocks.push_back(nextObject);
	}
	return lvl;
}

bool FileManager::saveLevel(const Level& level) {
	std::string path = level.name + ".lvl";
	std::cout << path << std::endl;
	std::ofstream levelFile(path);
	for (auto block : level.blocks) {
		std::string output = std::string("x:") + std::to_string(block.x) + std::string(" y:") + std::to_string(block.y) + std::string(" type:") + std::to_string(block.type) + "\n";
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