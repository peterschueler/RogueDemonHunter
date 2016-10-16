#include "../Include/Game.hpp"
#include "../Include/FileManager.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <random>

Game::Game(sf::RenderWindow& window) : window(window), bounds(0.f, 0.f, 480, 576), level(Level(1)), viewPort(window.getDefaultView()), movedDistance({0,0}), movingToNextLevel(false), currentLevel(1), monsterLoop(0), currentHealth(4), gameOver(false), didWin(false), bossPoints(4), bossScaler(7), transitionSoundPlaying(false) {
	EntityHeroine* her = new EntityHeroine();
	her->setPosition(50, 40);
	heroine = std::move(her);
	
	EntityHealthBar* bar = new EntityHealthBar();
	bar->setPosition(0,128);
	healthBar = std::move(bar);
	
	std::string backgroundPath = "Assets/Textures/Background_Stage_01.png";
	
	sf::IntRect rect = sf::IntRect(0,0,480,576);
	if (backgroundTexture.loadFromFile(backgroundPath)) {
		background.setTexture(backgroundTexture);
		background.setTextureRect(rect);
	} else {
		std::cerr << "ERROR! Couldn't load texture!" << std::endl;
	}
	
	if (!hitBuffer.loadFromFile("Assets/Sounds/Monster_Hit_01.ogg")) {
		std::cerr << "Sorry, couldn't load your sound effect." << std::endl;
	}
	hitSound.setBuffer(hitBuffer);
	
	if (!stepBuffer.loadFromFile("Assets/Sounds/Step_01.ogg")) {
		std::cerr << "Sorry, couldn't load your sound effect." << std::endl;
	}
	stepSound.setBuffer(stepBuffer);
	
	if (!healthBuffer.loadFromFile("Assets/Sounds/Health_Collected_01.ogg")) {
		std::cerr << "Sorry, couldn't load your sound effect." << std::endl;
	}
	healthSound.setBuffer(healthBuffer);
	
	if (!keyBuffer.loadFromFile("Assets/Sounds/Key_Found_01.ogg")) {
		std::cerr << "Sorry, couldn't load your sound effect." << std::endl;
	}
	keySound.setBuffer(keyBuffer);
	
	if (!transitionBuffer.loadFromFile("Assets/Sounds/Level_Transition_01.ogg")) {
		std::cerr << "Sorry, couldn't load your sound effect." << std::endl;
	}
	transitionSound.setBuffer(transitionBuffer);
	transitionSound.setLoop(true);
	
	setLevelCounter(currentLevel);
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
	window.draw(levelCounter);
}

void Game::input(Command* command) {
	command->execute(heroine);
	stepSound.play();
}

void Game::checkCollisions() {
	for (auto enemy : level.getEnemies()) {
		if (heroine->borders().intersects(enemy->borders())) {
			if (enemy->getType() == EntityEnemy::Type::eye) {
				currentHealth = currentHealth - 2;
			} else {
				currentHealth--;
			}
			healthBar->setHealth(currentHealth);
			if (enemy->getDirection().x != 0) {
				heroine->setPosition(enemy->getPosition().x + (3 * enemy->getDirection().x), heroine->getPosition().y); 
				hitSound.play();
				hitSound.play();
			} else if (enemy->getDirection().y != 0) {
				heroine->setPosition(enemy->getPosition().x, heroine->getPosition().y + (3 * enemy->getDirection().x));
				hitSound.play();
				hitSound.play();
			}
			if (currentHealth == 0) {
				gameOver = true;
			}
		}
	}
	
	for (auto button : level.getButtons()) {
		if (heroine->borders().intersects(button->borders())) {
			button->setDeleted(true);
			if (button->getType() == EntityButton::Type::healthPod) {
				currentHealth++;
				healthBar->setHealth(currentHealth);
				healthSound.play();
			} else if (button->getType() == EntityButton::Type::doorKey) {
				level.openDoors();
				keySound.play();
			} else {
				bossPoints--;
				bossScaler = bossScaler - 2;
				level.setBossScale(bossScaler);
				if (bossPoints == 0) {
					didWin = true;
					gameOver = true;
				}
			}
		}
	}
	for (auto wall : level.getWalls()) {
		if (heroine->borders().intersects(wall->borders())) {
			if (heroine->getPosition().x < 18) {
				heroine->setPosition(heroine->getPosition().x + 2, heroine->getPosition().y);	
				hitSound.play();
			} else if (heroine->getPosition().x > 142) {
				heroine->setPosition(heroine->getPosition().x - 2, heroine->getPosition().y);
				hitSound.play();
			}
			if (heroine->getPosition().y < 18) {
				heroine->setPosition(heroine->getPosition().x, heroine->getPosition().y + 2);
				hitSound.play();
			} else if (heroine->getPosition().y > 108) {
				heroine->setPosition(heroine->getPosition().x, heroine->getPosition().y - 2);
				hitSound.play();
			}
		}
	}
}

void Game::changeLevels(sf::Time delta) {
	if (movingToNextLevel == false) {
		if (heroine->getPosition().y > 127) {
			movedDistance = sf::Vector2f(0, 144);
			heroine->setPosition(heroine->getPosition().x, 124);
			movingToNextLevel = true;
			level.clearRoom();
		} else if (heroine->getPosition().y < 8) {
			movedDistance = sf::Vector2f(0, -144);
			heroine->setPosition(heroine->getPosition().x, 18);
			movingToNextLevel = true;
			level.clearRoom();
		} else if (heroine->getPosition().x > 159) {
			movedDistance = sf::Vector2f(160, 0);
			heroine->setPosition(152, heroine->getPosition().y);
			movingToNextLevel = true;
			level.clearRoom();
		} else if (heroine->getPosition().x < 9) {
			movedDistance = sf::Vector2f(-160, 0);
			heroine->setPosition(18, heroine->getPosition().y);
			movingToNextLevel = true;
			level.clearRoom();
		}
	} else {
		if (!transitionSoundPlaying) {
			transitionSoundPlaying = true;
			transitionSound.play();
		}
	}
	auto movement = 16 * delta.asSeconds();
	if (movedDistance.y == 144) {
		background.move(0, -movement);
		moved_y += movement;
		if (moved_y >= movedDistance.y) {
			level.closeWalls();
			movedDistance = sf::Vector2f({0,0});
			moved_y = 0;
			currentLevel++;
			movingToNextLevel = !level.moveToLevel(currentLevel);
			if (transitionSoundPlaying) {
				transitionSoundPlaying = false;
				transitionSound.stop();
			}
		}
	} else if (movedDistance.y == -144) {
		background.move(0, movement);
		moved_y -= movement;
		if (moved_y <= movedDistance.y) {
			level.closeWalls();
			movedDistance = sf::Vector2f({0,0});
			moved_y = 0;
			currentLevel++;
			movingToNextLevel	 = !level.moveToLevel(currentLevel);
			if (transitionSoundPlaying) {
				transitionSoundPlaying = false;
				transitionSound.stop();
			}
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
			if (transitionSoundPlaying) {
				transitionSoundPlaying = false;
				transitionSound.stop();
			}
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
			if (transitionSoundPlaying) {
				transitionSoundPlaying = false;
				transitionSound.stop();
			}
		}
	}
	setLevelCounter(currentLevel);
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

void Game::setLevelCounter(unsigned int lvl) {
	std::string levelCounterPath = "Assets/Textures/Levelcounter_01.png";
	if (levelCounterTexture.loadFromFile(levelCounterPath)) {
		levelCounter.setTexture(levelCounterTexture);
	} else {
		std::cerr << "ERROR! Couldn't load texture!" << std::endl;
	}
	switch (lvl) {
		case 1:
			levelCounter.setTextureRect(sf::IntRect(0,0,16,8));
			break;
		case 2:
			levelCounter.setTextureRect(sf::IntRect(16,0,16,8));
			break;
		case 3:
			levelCounter.setTextureRect(sf::IntRect(32,0,16,8));
			break;
		case 4:
			levelCounter.setTextureRect(sf::IntRect(0,8,16,8));
			break;
		case 5:
			levelCounter.setTextureRect(sf::IntRect(16,8,16,8));
			break;
		case 6:
			levelCounter.setTextureRect(sf::IntRect(32,8,16,8));
			break;
		case 7:
			levelCounter.setTextureRect(sf::IntRect(0,16,16,8));
			break;
		case 8:
			levelCounter.setTextureRect(sf::IntRect(16,16,16,8));
			break;
		case 9:
			levelCounter.setTextureRect(sf::IntRect(32,16,16,8));
			break;
		case 10:
			levelCounter.setTextureRect(sf::IntRect(0,24,16,8));
			break;
		case 11:
			levelCounter.setTextureRect(sf::IntRect(16,24,16,8));
			break;
		case 12:
			levelCounter.setTextureRect(sf::IntRect(32,24,16,8));
			break;
	}
	levelCounter.setPosition(12, 127);
}