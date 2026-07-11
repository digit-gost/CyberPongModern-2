#pragma once
#include "Entity.h"

enum class PowerUpType { SPEED_BOOST, BIG_PADDLE, TINY_PADDLE, INVISIBLE_BALL };

class PowerUp : public Entity {
public:
    PowerUp(sf::Vector2f pos, PowerUpType type);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void reset() override;
    sf::FloatRect getBounds() const override;

    PowerUpType getType() const { return type; }

private:
    PowerUpType type;
    sf::CircleShape shape;
    static constexpr float RADIUS = 14.f;

    sf::Color colorForType(PowerUpType t) const;
};