#include "../Include/Menu.hpp"

#include <iostream>
#include <string>

Menu::Menu(sf::RenderWindow& win) : window(win), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y) {

	std::string path = "Assets/Textures/Menu_Background_02.png";
	if (texture.loadFromFile(path)) {
		sprite.setTexture(texture);
	}
	sprite.setColor(sf::Color(170,190,15));
	
	std::string blinky_path = "Assets/Textures/Monsters_Sheet_01.png";
	if (bl_texture.loadFromFile(blinky_path)) {
		currentStep = first;
		blinky.setTexture(bl_texture);
		blinky.setTextureRect(sf::IntRect(32,16,8,8));
	}
	blinky.setPosition(115,70);
	blinky.setColor(sf::Color(170,190,15));
	
// 	if (!theme.openFromFile("Assets/Music/menu.ogg")) {
// 	}
// 	theme.setLoop(true);
// 	theme.play();
}

bool Menu::update(sf::Time delta) {
	animationTimer += delta.asSeconds();
	if (animationTimer >= 0.3) {
		animate();
		animationTimer = 0;
	}
	return true;
}

void Menu::draw() {
	window.draw(sprite);
	window.draw(blinky);
}

void Menu::animate() {
	if (currentStep == first) {
		blinky.setScale({1,1});
		blinky.setTextureRect(sf::IntRect(40,16,8,8));
		currentStep = second;
	} else if (currentStep == second) {
		blinky.setTextureRect(sf::IntRect(32,16,8,8));
		currentStep = third;
	} else if (currentStep == third) {
		blinky.setTextureRect(sf::IntRect(32,24,8,8));
		blinky.setScale({-1,1});
		currentStep = fourth;
	} else if (currentStep == fourth) {
		blinky.setTextureRect(sf::IntRect(40,16,8,8));
		currentStep = fifth;
	} else if (currentStep == fifth) {
		blinky.setTextureRect(sf::IntRect(32,16,8,8));
		currentStep = sixth;
	} else if (currentStep == sixth) {
		blinky.setTextureRect(sf::IntRect(32,24,8,8));
		currentStep = first;
	}
}