#pragma once
#include <SFML/Graphics.hpp>
#include "../entities/PowerUp.h"
#include "../entities/Ball.h"
#include "../entities/Paddle.h"
#include <memory>

class PowerUpSystem {
public:
    void update(float dt, Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer);
    void draw(sf::RenderWindow& window);

private:
    std::unique_ptr<PowerUp> activePowerUp;
    float spawnTimer = SPAWN_INTERVAL;

    bool speedBoostActive = false;
    float speedBoostTimer = 0.f;

    bool bigPaddleActive = false;
    float bigPaddleTimer = 0.f;
    Paddle::Side bigPaddleSide = Paddle::Side::LEFT;

    bool tinyPaddleActive = false;
    float tinyPaddleTimer = 0.f;
    Paddle::Side tinyPaddleSide = Paddle::Side::LEFT;

    bool invisibleBallActive = false;
    float invisibleBallTimer = 0.f;

    static constexpr float SPAWN_INTERVAL = 15.f;
    static constexpr float EFFECT_DURATION = 8.f;
    static constexpr float INVISIBLE_DURATION = 3.f;

    void trySpawn(float dt);
    void checkCollision(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer);
    void applyEffect(PowerUpType type, Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer);
    void updateEffects(float dt, Paddle& paddleLeft, Paddle& paddleRight, Ball& ball);
};