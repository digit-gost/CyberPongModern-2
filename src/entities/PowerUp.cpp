#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f pos, PowerUpType type_) : type(type_) {
    position = pos;
    shape.setRadius(RADIUS);
    shape.setOrigin({RADIUS, RADIUS});
    shape.setPosition(position);
    shape.setFillColor(colorForType(type));
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::White);
}

void PowerUp::update(float /*dt*/) {
    shape.setPosition(position);
}

void PowerUp::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void PowerUp::reset() {
    // Un power-up est détruit après usage par PowerUpSystem, pas besoin de le réinitialiser.
}

sf::FloatRect PowerUp::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Color PowerUp::colorForType(PowerUpType t) const {
    switch (t) {
        case PowerUpType::SPEED_BOOST:    return sf::Color::Red;
        case PowerUpType::BIG_PADDLE:     return sf::Color::Green;
        case PowerUpType::TINY_PADDLE:    return sf::Color(148, 0, 211);
        case PowerUpType::INVISIBLE_BALL: return sf::Color::White;
    }
    return sf::Color::White;
}