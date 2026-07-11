#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "../entities/PowerUp.h"
#include "../entities/Ball.h"
#include "../entities/Paddle.h"

class PowerUpSystem {
public:
    void update(float dt, std::vector<std::unique_ptr<Ball>>& balls,
                Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer);
    void draw(sf::RenderWindow& window);

    // Renvoie true une seule fois quand TWIN BALL doit creer une nouvelle
    // balle ; remplit sourceBall avec la balle a cloner.
    bool consumeTwinBallRequest(Ball*& sourceBall);

private:
    std::unique_ptr<PowerUp> activePowerUp;
    float spawnTimer = SPAWN_INTERVAL;

    bool speedActive = false;
    float speedTimer = 0.f;
    float speedFactorApplied = 1.f;
    Ball* speedBall = nullptr;

    bool invisibleActive = false;
    float invisibleTimer = 0.f;
    Ball* invisibleBall = nullptr;

    bool bigPaddleActive = false;
    float bigPaddleTimer = 0.f;
    Paddle::Side bigPaddleSide = Paddle::Side::LEFT;

    bool tinyPaddleActive = false;
    float tinyPaddleTimer = 0.f;
    Paddle::Side tinyPaddleSide = Paddle::Side::LEFT;

    bool twinBallRequested = false;
    Ball* twinBallSource = nullptr;

    static constexpr float SPAWN_INTERVAL = 15.f;
    static constexpr float EFFECT_DURATION = 8.f;
    static constexpr float INVISIBLE_DURATION = 3.f;

    void trySpawn(float dt);
    void checkCollision(std::vector<std::unique_ptr<Ball>>& balls,
                         Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer);
    void applyEffect(PowerUpType type, Ball& ball,
                      Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer);
    void updateEffects(float dt, std::vector<std::unique_ptr<Ball>>& balls,
                        Paddle& paddleLeft, Paddle& paddleRight);

    bool ballStillExists(Ball* ptr, std::vector<std::unique_ptr<Ball>>& balls) const;
};