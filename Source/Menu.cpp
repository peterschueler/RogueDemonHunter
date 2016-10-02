#include "../Include/Menu.hpp"

#include <iostream>
#include <string>

Menu::Menu(sf::RenderWindow& win) : window(win), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y) {
}

bool Menu::update(sf::Time delta) {
	return true;
}

void Menu::draw() {
}