#include "Ball.h"
#include <cmath>
#include <cstdint>

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
    updateTrail();
}

void Ball::updateTrail() {
    trail.push_back(position);
    if ((int)trail.size() > TRAIL_LEN) {
        trail.pop_front();
    }
}

void Ball::drawTrail(sf::RenderWindow& window) {
    int n = (int)trail.size();
    for (int i = 0; i < n; ++i) {
        float t = (float)(i + 1) / (float)n; // 0 (vieux) -> 1 (recent)
        auto alpha = (std::uint8_t)(t * 120.f);

        sf::CircleShape dot(radius * t * 0.8f);
        dot.setOrigin({dot.getRadius(), dot.getRadius()});
        dot.setPosition(trail[i]);
        dot.setFillColor(sf::Color(0, 255, 255, alpha));
        window.draw(dot);
    }
}

void Ball::draw(sf::RenderWindow& window) {
    drawTrail(window);
    window.draw(shape);
}

void Ball::reset() {
    position = startPosition;
    velocity = {INITIAL_SPEED, INITIAL_SPEED * 0.5f};
    speedMultiplier = 1.f;
    visible = true;
    trail.clear();
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