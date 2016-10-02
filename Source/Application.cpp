#include "../Include/Application.hpp"
#include "../Include/MenuState.hpp"
#include "../Include/GameState.hpp"

const sf::Time Application::secondsFramesRatio = sf::seconds(1.f/60.f);

Application::Application() : window(sf::VideoMode(160,144), "RogueDemonHunter") {
	enterState(new MenuState(window));
}

Application::Application(Settings& newSettings) : window(sf::VideoMode(newSettings.display_y, newSettings.display_x), newSettings.display_title) {
	enterState(new MenuState(window));
}

void Application::run() {
	sf::Clock clock;
	sf::Time lastUpdate = sf::Time::Zero;
	while (window.isOpen()) {
		lastUpdate += clock.restart();
		while (lastUpdate > secondsFramesRatio) {
			lastUpdate -= secondsFramesRatio;
			
			processInput();
			update(secondsFramesRatio);
		}
		render();
	}
}

void Application::processInput() {
	sf::Event event;
	if (currentState->processInput(event) == false) {
		enterState(currentState->onExit());
	}
}

void Application::update(sf::Time delta) {
	if (currentState->update(delta) == false) {
		enterState(currentState->onExit());
	}
}

void Application::render() {
	currentState->render();
}

void Application::enterState(State* state) {
	state->onEntry(currentState);
	currentState = state;
}