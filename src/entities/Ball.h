#pragma once
#include "Entity.h"
#include <deque>

class Ball : public Entity {
public:
    Ball(sf::Vector2f startPos, float radius = 10.f);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void reset() override;
    sf::FloatRect getBounds() const override;

    void applySpeedMultiplier(float factor);
    void setVisible(bool v);
    float getRadius() const { return radius; }

    void move(sf::Vector2f offset);

    static constexpr float INITIAL_SPEED = 350.f;

private:
    float radius;
    sf::CircleShape shape;
    sf::Vector2f startPosition;
    bool visible = true;
    float speedMultiplier = 1.f;

    std::deque<sf::Vector2f> trail;
    static constexpr int TRAIL_LEN = 8;

    void updateTrail();
    void drawTrail(sf::RenderWindow& window);
};