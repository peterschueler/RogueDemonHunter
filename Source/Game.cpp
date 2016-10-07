#include "../Include/Game.hpp"
#include "../Include/FileManager.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

Game::Game(sf::RenderWindow& window) : window(window), bounds(0.f, 0.f, 480, 576), currentLevel(Level("Assets/Levels/one")) {
	EntityHeroine* her = new EntityHeroine();
	her->setPosition(50, 40);
// 	her->setScale(2.f, 2.f);
	heroine = std::move(her);
	
	std::string backgroundPath = "Assets/Textures/Background_Stage_01.png";
	
	sf::IntRect rect = sf::IntRect(0,0,480,576);
	if (backgroundTexture.loadFromFile(backgroundPath)) {
		background.setTexture(backgroundTexture);
		background.setTextureRect(rect);
	} else {
		std::cerr << "ERROR! Couldn't load texture!" << std::endl;
	}
}

bool Game::update(sf::Time delta) {
	checkCollisions();
	heroine->update(delta);
	return true;
}

void Game::draw() {
	window.draw(background);
	window.draw(*heroine);
	
	for (auto wall : currentLevel.getWalls()) {
		window.draw(*wall);
	}
}

void Game::input(Command* command) {
	command->execute(heroine);
}

void Game::checkCollisions() {
	if (heroine->getPosition().x < 18) {
		heroine->setPosition(heroine->getPosition().x + 2, heroine->getPosition().y);	
	} else if (heroine->getPosition().x > 142) {
		heroine->setPosition(heroine->getPosition().x - 2, heroine->getPosition().y);
	}
	if (heroine->getPosition().y < 18) {
		heroine->setPosition(heroine->getPosition().x, heroine->getPosition().y + 2);
	} else if (heroine->getPosition().y > 126) {
		heroine->setPosition(heroine->getPosition().x, heroine->getPosition().y - 2);
	}
}