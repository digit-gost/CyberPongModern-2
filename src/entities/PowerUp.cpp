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
    // Un power-up est detruit apres usage par PowerUpSystem.
}

sf::FloatRect PowerUp::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Color PowerUp::colorForType(PowerUpType t) const {
    switch (t) {
        case PowerUpType::SPEED_BOOST:    return sf::Color::Red;
        case PowerUpType::SLOW_MO:        return sf::Color::Blue;
        case PowerUpType::BIG_PADDLE:     return sf::Color::Green;
        case PowerUpType::TINY_PADDLE:    return sf::Color(148, 0, 211);
        case PowerUpType::INVISIBLE_BALL: return sf::Color::White;
        case PowerUpType::TWIN_BALL:      return sf::Color(255, 215, 0); // or
    }
    return sf::Color::White;
}