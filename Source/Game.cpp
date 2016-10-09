#include "../Include/Game.hpp"
#include "../Include/FileManager.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <random>

Game::Game(sf::RenderWindow& window) : window(window), bounds(0.f, 0.f, 480, 576), level(Level(1)), viewPort(window.getDefaultView()), movedDistance({0,0}), movingToNextLevel(false), currentLevel(1), monsterLoop(0), currentHealth(4), gameOver(false) {
	EntityHeroine* her = new EntityHeroine();
	her->setPosition(50, 40);
	heroine = std::move(her);
	
	EntityHealthBar* bar = new EntityHealthBar();
	bar->setPosition(0,128);
	healthBar = std::move(bar);
	
	for (auto wall : level.getWalls()) {
		if (wall->getType() == EntityWall::Type::outer_first || wall->getType() == EntityWall::Type::outer_second || wall->getType() == EntityWall::Type::outer_door || wall->getType() == EntityWall::Type::outer_third) {
			std::cout << "wall x: " << wall->getPosition().x << " wall y: " << wall->getPosition().y << std::endl;
		}
	}
	
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
	 // TODO: find a place to call this (-> menu!)
		for (auto enemy : level.getEnemies()) {
			enemy->setColor(sf::Color(170,190,15));
		}
		for (auto wall : level.getWalls()) {
			wall->setColor(sf::Color(170,190,15));
		}
		for (auto button : level.getButtons()) {
			button->setColor(sf::Color(170,190,15));
		}
		heroine->setColor(sf::Color(170,190,15));
		background.setColor(sf::Color(170,190,15));
		healthBar->setColor(sf::Color(170,190,15));
	checkCollisions();
	moveMonsters(delta);
	if (!movingToNextLevel) {
		heroine->update(delta);
		healthBar->update(delta);	
		for (auto enemy : level.getEnemies()) {
			enemy->update(delta);
		}
	}
	for (auto wall : level.getWalls()) {
		wall->update(delta);
	}
	changeLevels(delta);
	return !gameOver;
}

void Game::draw() {
	window.setView(viewPort);
	window.draw(background);
	for (auto button : level.getButtons()) {
		window.draw(*button);
	}
	window.draw(*heroine);
	
	for (auto enemy : level.getEnemies()) {
		window.draw(*enemy);
	}
	
	for (auto wall : level.getWalls()) {
		window.draw(*wall);
	}
	window.draw(*healthBar);
}

void Game::input(Command* command) {
	command->execute(heroine);
}

void Game::checkCollisions() {
	for (auto enemy : level.getEnemies()) {
		if (heroine->borders().intersects(enemy->borders())) {
			currentHealth--;
			healthBar->setHealth(currentHealth);
			if (enemy->getDirection().x != 0) {
				heroine->setPosition(enemy->getPosition().x + (3 * enemy->getDirection().x), heroine->getPosition().y); 
			} else if (enemy->getDirection().y != 0) {
				heroine->setPosition(enemy->getPosition().x, heroine->getPosition().y + (3 * enemy->getDirection().x)); 
			}
			if (currentHealth == 0) {
				gameOver = true;
			}
		}
	}
	
	for (auto button : level.getButtons()) {
		if (heroine->borders().intersects(button->borders())) {
			button->setDeleted(true);
			level.openDoors();
		}
	}
	for (auto wall : level.getWalls()) {
		if (heroine->borders().intersects(wall->borders())) {
			if (heroine->getPosition().x < 18) {
				heroine->setPosition(heroine->getPosition().x + 2, heroine->getPosition().y);	
			} else if (heroine->getPosition().x > 142) {
				heroine->setPosition(heroine->getPosition().x - 2, heroine->getPosition().y);
			}
			if (heroine->getPosition().y < 18) {
				heroine->setPosition(heroine->getPosition().x, heroine->getPosition().y + 2);
			} else if (heroine->getPosition().y > 118) {
				heroine->setPosition(heroine->getPosition().x, heroine->getPosition().y - 2);
			}
		}
	}
}

void Game::changeLevels(sf::Time delta) {
	if (movingToNextLevel == false) {
		if (heroine->getPosition().y > 127) {
			movedDistance = sf::Vector2f(0, 120);
			heroine->setPosition(heroine->getPosition().x, 124);
			movingToNextLevel = true;
			level.clearRoom();
		} else if (heroine->getPosition().y < 8) {
			movedDistance = sf::Vector2f(0, -120);
			heroine->setPosition(heroine->getPosition().x, 18);
			movingToNextLevel = true;
			level.clearRoom();
		} else if (heroine->getPosition().x > 151) {
			movedDistance = sf::Vector2f(160, 0);
			heroine->setPosition(142, heroine->getPosition().y);
			movingToNextLevel = true;
			level.clearRoom();
		} else if (heroine->getPosition().x < 9) {
			movedDistance = sf::Vector2f(-160, 0);
			heroine->setPosition(18, heroine->getPosition().y);
			movingToNextLevel = true;
			level.clearRoom();
		}
	}
	auto movement = 16 * delta.asSeconds();
	if (movedDistance.y == 120) {
		background.move(0, -movement);
		moved_y += movement;
		if (moved_y >= movedDistance.y) {
			level.closeWalls();
			movedDistance = sf::Vector2f({0,0});
			moved_y = 0;
			currentLevel++;
			movingToNextLevel = !level.moveToLevel(currentLevel);
		}
	} else if (movedDistance.y == -120) {
		background.move(0, movement);
		moved_y -= movement;
		if (moved_y <= movedDistance.y) {
			level.closeWalls();
			movedDistance = sf::Vector2f({0,0});
			moved_y = 0;
			currentLevel++;
			movingToNextLevel	 = !level.moveToLevel(currentLevel);
		}
	}
	if (movedDistance.x == 160) {
		background.move(-movement, 0);
		moved_x += movement;
		if (moved_x >= movedDistance.x) {
			level.closeWalls();
			movedDistance = sf::Vector2f({0,0});
			moved_x = 0;
			currentLevel++;
			movingToNextLevel = !level.moveToLevel(currentLevel);
		}
	} else if (movedDistance.x == -160) {
		background.move(movement,0);
		moved_x -= movement;
		if (moved_x <= movedDistance.x) {
			level.closeWalls();
			movedDistance = sf::Vector2f({0,0});
			moved_x = 0;
			currentLevel++;
			movingToNextLevel = !level.moveToLevel(currentLevel);
		}
	}
}

void Game::moveMonsters(sf::Time delta) {
	monsterLoop += delta.asSeconds();
	if (monsterLoop > 0.5) {
		for (auto enemy : level.getEnemies()) {
			enemy->walk();
			monsterLoop = 0;
		}
	}
}