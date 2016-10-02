#include "../Include/Config.h"
#include "../Include/Application.hpp"
#include "../Include/Settings.hpp"

#include <iostream>
#include <fstream>

int main() {
	try {
		std::cout << "***\n\nWelcome to RogueDemonHunter!\n\n***" << std::endl;
		Application app;
		app.run();
	} catch (std::exception& e) {
		std::cout << "\nFAILED: " <<e.what() << std::endl;
	}
}