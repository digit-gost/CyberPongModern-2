#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../entities/Ball.h"
#include "../entities/Paddle.h"
#include "../systems/PhysicsSystem.h"

// Jour 1 : pas encore de Pattern State (arrive Jour 2).
// Game gère directement la boucle et une partie 2 joueurs simple.
class Game {
public:
    Game();
    void run();

    static constexpr int WINDOW_W = 1280;
    static constexpr int WINDOW_H = 720;

private:
    sf::RenderWindow window;

    std::unique_ptr<Ball> ball;
    std::unique_ptr<Paddle> paddleLeft;
    std::unique_ptr<Paddle> paddleRight;
    PhysicsSystem physics;

    void processEvents();
    void handlePaddleInput(float dt);
    void update(float dt);
    void render();
};
