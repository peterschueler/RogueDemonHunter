#include "../Include/Settings.hpp"

#include <sstream>

std::vector<std::string> split(const std::string& line, const char character) {
	std::vector<std::string> results;
	std::string::size_type i = 0;
	
	while (i != line.size() && isspace(line[i])) {
		++i;
	}
	
	std::string::size_type j = i;
	while (j != line.size() && isspace(line[j])) {
		++j;
	}
	
	if (i != j) {
		results.push_back(line.substr(i, j-i));
		i = j;
	}
	return results;
}

Settings parse(std::istream& input, const char character) {
	std::string line;
	Settings newSettings;
	while (std::getline(input, line)) {
		std::vector<std::string> settings = split(line, character);
		if (settings.front() == "display_x") {
			std::stringstream(settings.back()) >> newSettings.display_x;
		} else if (settings.front() == "display_y") {
			std::stringstream(settings.back()) >> newSettings.display_y;
		} else if (settings.front() == "display_title") {
			newSettings.display_title = settings.back();
		}
	}
	return newSettings;
}