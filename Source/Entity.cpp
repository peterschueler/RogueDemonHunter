#include "../Include/Entity.hpp"

Entity::Entity(): gravityOn(false), bottom(0.f), color(sf::Color::Transparent) {
	attachTexture();
// 	sprite.setColor(color);
}

void Entity::update(sf::Time delta) {
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	
	target.draw(sprite, states);
}

void Entity::attachTexture() {
}

sf::FloatRect Entity::borders() const {
	sf::FloatRect bounds = getTransform().transformRect(sprite.getGlobalBounds());
	return bounds;
}

void Entity::setDirection(float x, float y) {
	direction.x = x;
	direction.y = y;
}

sf::Vector2f Entity::getDirection() const {
	return direction;
}

void Entity::setColor(sf::Color col) {
	color = col;
}

void Entity::setGrounded(float bot) {
	setPosition(sf::Vector2f(getPosition().x, bot));
	bottom = bot;
}

float Entity::getGrounded() const {
	return bottom;
}

void Entity::applyGravity(bool now) {
	gravityOn = now;
}