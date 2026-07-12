#include "Paddle.h"
#include <algorithm>

namespace {
    constexpr int SCREEN_H = 720;
}

Paddle::Paddle(sf::Vector2f startPos, Side side_)
    : side(side_), startPosition(startPos)
{
    position = startPos;
    shape.setSize({WIDTH, BASE_HEIGHT});
    shape.setOrigin({WIDTH / 2.f, BASE_HEIGHT / 2.f});
    shape.setPosition(position);

    baseColor = (side == Side::LEFT) ? sf::Color::Cyan : sf::Color::Magenta;
    shape.setFillColor(baseColor);
}

void Paddle::update(float dt) {
    clampToScreen();
    shape.setSize({WIDTH, BASE_HEIGHT * heightScale});
    shape.setOrigin({WIDTH / 2.f, (BASE_HEIGHT * heightScale) / 2.f});
    shape.setPosition(position);

    if (flashTimer > 0.f) {
        flashTimer -= dt;
        shape.setFillColor(sf::Color::White);
    } else {
        shape.setFillColor(baseColor);
    }
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Paddle::reset() {
    position = startPosition;
    heightScale = 1.f;
    velocity = {0.f, 0.f};
    flashTimer = 0.f;
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

void Paddle::moveUp(float dt) {
    position.y -= SPEED * dt;
}

void Paddle::moveDown(float dt) {
    position.y += SPEED * dt;
}

void Paddle::setHeightScale(float scale) {
    heightScale = scale;
}

void Paddle::triggerFlash() {
    flashTimer = FLASH_DURATION;
}

void Paddle::clampToScreen() {
    float halfHeight = (BASE_HEIGHT * heightScale) / 2.f;
    position.y = std::clamp(position.y, halfHeight, (float)SCREEN_H - halfHeight);
}