#include "Ball.h"
#include <cmath>

Ball::Ball(sf::Vector2f startPos, float radius_)
    : radius(radius_), startPosition(startPos)
{
    position = startPos;
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White);
    reset();
}

void Ball::update(float dt) {
    position += velocity * dt;
    shape.setPosition(position);
    shape.setFillColor(visible ? sf::Color::White : sf::Color(255, 255, 255, 60));
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Ball::reset() {
    position = startPosition;
    // Direction initiale simple en diagonale (variée au Jour 2 avec du hasard)
    velocity = {INITIAL_SPEED, INITIAL_SPEED * 0.5f};
    speedMultiplier = 1.f;
    visible = true;
    shape.setPosition(position);
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

void Ball::applySpeedMultiplier(float factor) {
    speedMultiplier = factor;
    velocity *= factor;
}

void Ball::setVisible(bool v) {
    visible = v;
}

void Ball::move(sf::Vector2f offset) {
    position += offset;
    shape.setPosition(position);
}
