#include "../Include/EndMenu.hpp"

#include <iostream>
#include <string>

EndMenu::EndMenu(sf::RenderWindow& win, bool didWin) : window(win), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y) {
	std::string path;
	if (didWin) {
		path = "Assets/Textures/Victory_Screen_01.png";
	} else {
		path = "Assets/Textures/Defeat_Screen_01.png";
	}
	if (texture.loadFromFile(path)) {
		background.setTexture(texture);
	}
	background.setColor(sf::Color(170,190,15));
}

void EndMenu::update(sf::Time delta) {
}

void EndMenu::draw() {
	window.draw(background);
}