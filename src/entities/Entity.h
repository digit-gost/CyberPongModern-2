#pragma once
#include <SFML/Graphics.hpp>

// Classe de base abstraite pour toutes les entités du jeu (Ball, Paddle,
// PowerUp, Particle...). Impose une interface commune : chaque entité
// concrète DOIT implémenter update/draw/reset/getBounds.
class Entity {
protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool active = true;

public:
    virtual ~Entity() = default;

    // Interface pure — chaque entité DOIT implémenter ces méthodes
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void reset() = 0;

    // Accesseurs communs
    virtual sf::FloatRect getBounds() const = 0;

    bool isActive() const { return active; }
    void setActive(bool a) { active = a; }

    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getVelocity() const { return velocity; }
    void setVelocity(sf::Vector2f v) { velocity = v; }
};
