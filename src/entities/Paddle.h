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

    // Déplacement contrôlé par le clavier (appelé depuis Game::processEvents/update)
    void moveUp(float dt);
    void moveDown(float dt);

    bool isLeftSide() const { return side == Side::LEFT; }
    Side getSide() const { return side; }

    // Utilisé par les power-ups BIG PADDLE / TINY PADDLE (Jour 3)
    void setHeightScale(float scale);

    static constexpr float WIDTH = 20.f;
    static constexpr float BASE_HEIGHT = 100.f;
    static constexpr float SPEED = 500.f; // pixels/seconde

private:
    sf::RectangleShape shape;
    Side side;
    sf::Vector2f startPosition;
    float heightScale = 1.f;

    void clampToScreen();
};
