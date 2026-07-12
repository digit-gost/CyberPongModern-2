#pragma once
#include "Entity.h"

class Paddle : public Entity {
public:
    enum class Side { LEFT, RIGHT };

    Paddle(sf::Vector2f startPos, Side side);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void reset() override;
    sf::FloatRect getBounds() const override;

    void moveUp(float dt);
    void moveDown(float dt);

    bool isLeftSide() const { return side == Side::LEFT; }
    Side getSide() const { return side; }

    void setHeightScale(float scale);
    void triggerFlash(); // effet visuel a l'impact (obligatoire, section 2.1.4)

    static constexpr float WIDTH = 20.f;
    static constexpr float BASE_HEIGHT = 100.f;
    static constexpr float SPEED = 500.f;

private:
    sf::RectangleShape shape;
    Side side;
    sf::Vector2f startPosition;
    float heightScale = 1.f;
    sf::Color baseColor;

    float flashTimer = 0.f;
    static constexpr float FLASH_DURATION = 0.12f;

    void clampToScreen();
};