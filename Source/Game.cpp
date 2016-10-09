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
	checkCollisions();
	heroine->update(delta);
	for (auto wall : currentLevel.getWalls()) {
		wall->update(delta);
	}
	changeLevels(delta);
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

void Game::changeLevels(sf::Time delta) {
	auto movement = 16 * delta.asSeconds();
	if (movedDistance.y == 144) {
		background.move(0, -movement);
		moved_y += movement;
		if (moved_y >= movedDistance.y) {
			movedDistance = sf::Vector2f({0,0});
			moved_y = 0;
			movingToNextLevel = false;
		}
	} else if (movedDistance.y == -144) {
		background.move(0, movement);
		moved_y += movement;
		if (moved_y >= movedDistance.y) {
			movedDistance = sf::Vector2f({0,0});
			moved_y = 0;
			movingToNextLevel = false;
		}
	}
	if (movedDistance.x == 160) {
		background.move(-movement, 0);
		moved_x += movement;
		if (moved_x >= movedDistance.x) {
			movedDistance = sf::Vector2f({0,0});
			moved_x = 0;
			movingToNextLevel = false;
		}
	} else if (movedDistance.x == 160) {
		background.move(movement,0);
		moved_x += movement;
		if (moved_x >= movedDistance.x) {
			movedDistance = sf::Vector2f({0,0});
			moved_x = 0;
			movingToNextLevel = false;
		}
	}
}