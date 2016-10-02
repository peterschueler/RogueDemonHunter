#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include <vector>

#include "Level.hpp"
#include "Settings.hpp"

std::vector<std::string> split_str(const std::string&, char);

class FileManager {
public:
	static Level loadLevel(const std::string&);
	static bool saveLevel(const Level&);
	
	static void loadSettings(const std::string&);
	static bool saveSettings(const Settings&);
	
private:
	static std::vector<std::string> parseFile(const std::string&);
};

#endif