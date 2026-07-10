#pragma once
#include "Entity.h"

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

    // Utilisé par PhysicsSystem pour corriger la position après collision
    void move(sf::Vector2f offset);

    static constexpr float INITIAL_SPEED = 350.f; // pixels/seconde

private:
    float radius;
    sf::CircleShape shape;
    sf::Vector2f startPosition;
    bool visible = true;
    float speedMultiplier = 1.f;
    // NOTE (Jour 3) : ajouter std::deque<sf::Vector2f> trail pour l'effet
    // de trainée lumineuse (8 dernières positions) + drawTrail().
};
