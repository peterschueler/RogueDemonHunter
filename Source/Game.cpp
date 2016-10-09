#include "../Include/Game.hpp"
#include "../Include/FileManager.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

Game::Game(sf::RenderWindow& window) : window(window), bounds(0.f, 0.f, 480, 576), currentLevel(Level("Assets/Levels/one")), viewPort(window.getDefaultView()), movedDistance({0,0}), movingToNextLevel(false) {
	EntityHeroine* her = new EntityHeroine();
	her->setPosition(50, 40);
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
	if (movedDistance.y != 0) {
		viewPort.move(0, 16 * delta.asSeconds());
		moved_y += 16 * delta.asSeconds();
		std::cout << moved_y << std::endl;
		if (moved_y >= 144) {
			movedDistance = sf::Vector2f({0,0});
			moved_y = 0;
			movingToNextLevel = false;
		}
	}
	checkCollisions();
	heroine->update(delta);
	for (auto wall : currentLevel.getWalls()) {
		wall->update(delta);
	}
	return true;
}

void Game::draw() {
	window.setView(viewPort);
	window.draw(background);
	for (auto button : currentLevel.getButtons()) {
		window.draw(*button);
	}
	window.draw(*heroine);
	
	for (auto wall : currentLevel.getWalls()) {
		window.draw(*wall);
	}
}

void Game::input(Command* command) {
	command->execute(heroine);
}

void Game::checkCollisions() {
	for (auto button : currentLevel.getButtons()) {
		if (heroine->borders().intersects(button->borders())) {
			button->setDeleted(true);
			currentLevel.openDoors();
		}
	}
	if (heroine->getPosition().y > 135 && movingToNextLevel == false) {
		movedDistance = sf::Vector2f(0, 144);
		movingToNextLevel = true;
	}
	for (auto wall : currentLevel.getWalls()) {
		if (heroine->borders().intersects(wall->borders())) {
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
	}
}