#include "../Include/Game.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

Game::Game(sf::RenderWindow& window) : window(window), bounds(0.f, 0.f, window.getDefaultView().getSize().x, window.getDefaultView().getSize().y) {
}

bool Game::update(sf::Time delta) {
	return true;
}

void Game::draw() {
}

void Game::input(Command* command) {
}