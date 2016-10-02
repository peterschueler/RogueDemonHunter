#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct Settings {
	unsigned int display_x;
	unsigned int display_y;
	std::string display_title;
};

std::vector<std::string> split(const std::string&, const char);
Settings parse(std::istream& input, const char);

#endif