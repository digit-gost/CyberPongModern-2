#include "PowerUpSystem.h"
#include "../core/Game.h"
#include <random>

namespace {
    std::mt19937& rng() {
        static std::mt19937 gen{std::random_device{}()};
        return gen;
    }

    PowerUpType randomType() {
        std::uniform_int_distribution<int> dist(0, 5);
        return static_cast<PowerUpType>(dist(rng()));
    }
}

void PowerUpSystem::trySpawn(float dt) {
    if (activePowerUp) return;

    spawnTimer -= dt;
    if (spawnTimer <= 0.f) {
        sf::Vector2f center(Game::WINDOW_W / 2.f, Game::WINDOW_H / 2.f);
        activePowerUp = std::make_unique<PowerUp>(center, randomType());
        spawnTimer = SPAWN_INTERVAL;
    }
}

bool PowerUpSystem::ballStillExists(Ball* ptr, std::vector<std::unique_ptr<Ball>>& balls) const {
    for (auto& b : balls) {
        if (b.get() == ptr) return true;
    }
    return false;
}

void PowerUpSystem::checkCollision(std::vector<std::unique_ptr<Ball>>& balls,
                                    Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer) {
    if (!activePowerUp || balls.empty()) return;

    // Seule la balle principale (balls[0]) peut activer un power-up.
    Ball& mainBall = *balls[0];
    if (mainBall.getBounds().findIntersection(activePowerUp->getBounds()).has_value()) {
        applyEffect(activePowerUp->getType(), mainBall, paddleLeft, paddleRight, lastScorer);
        activePowerUp.reset();
    }
}

void PowerUpSystem::applyEffect(PowerUpType type, Ball& ball,
                                 Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer) {
    switch (type) {
        case PowerUpType::SPEED_BOOST:
            ball.applySpeedMultiplier(1.5f);
            speedFactorApplied = 1.5f;
            speedActive = true;
            speedTimer = EFFECT_DURATION;
            speedBall = &ball;
            break;

        case PowerUpType::SLOW_MO:
            ball.applySpeedMultiplier(0.4f);
            speedFactorApplied = 0.4f;
            speedActive = true;
            speedTimer = EFFECT_DURATION;
            speedBall = &ball;
            break;

        case PowerUpType::BIG_PADDLE: {
            bigPaddleSide = lastScorer;
            Paddle& target = (bigPaddleSide == Paddle::Side::LEFT) ? paddleLeft : paddleRight;
            target.setHeightScale(2.f);
            bigPaddleActive = true;
            bigPaddleTimer = EFFECT_DURATION;
            break;
        }

        case PowerUpType::TINY_PADDLE: {
            tinyPaddleSide = (lastScorer == Paddle::Side::LEFT) ? Paddle::Side::RIGHT : Paddle::Side::LEFT;
            Paddle& target = (tinyPaddleSide == Paddle::Side::LEFT) ? paddleLeft : paddleRight;
            target.setHeightScale(0.5f);
            tinyPaddleActive = true;
            tinyPaddleTimer = EFFECT_DURATION;
            break;
        }

        case PowerUpType::INVISIBLE_BALL:
            ball.setVisible(false);
            invisibleActive = true;
            invisibleTimer = INVISIBLE_DURATION;
            invisibleBall = &ball;
            break;

        case PowerUpType::TWIN_BALL:
            twinBallRequested = true;
            twinBallSource = &ball;
            break;
    }
}

void PowerUpSystem::updateEffects(float dt, std::vector<std::unique_ptr<Ball>>& balls,
                                   Paddle& paddleLeft, Paddle& paddleRight) {
    if (speedActive) {
        speedTimer -= dt;
        if (speedTimer <= 0.f) {
            if (speedBall && ballStillExists(speedBall, balls)) {
                speedBall->applySpeedMultiplier(1.f / speedFactorApplied);
            }
            speedActive = false;
            speedBall = nullptr;
        }
    }

    if (invisibleActive) {
        invisibleTimer -= dt;
        if (invisibleTimer <= 0.f) {
            if (invisibleBall && ballStillExists(invisibleBall, balls)) {
                invisibleBall->setVisible(true);
            }
            invisibleActive = false;
            invisibleBall = nullptr;
        }
    }

    if (bigPaddleActive) {
        bigPaddleTimer -= dt;
        if (bigPaddleTimer <= 0.f) {
            Paddle& target = (bigPaddleSide == Paddle::Side::LEFT) ? paddleLeft : paddleRight;
            target.setHeightScale(1.f);
            bigPaddleActive = false;
        }
    }

    if (tinyPaddleActive) {
        tinyPaddleTimer -= dt;
        if (tinyPaddleTimer <= 0.f) {
            Paddle& target = (tinyPaddleSide == Paddle::Side::LEFT) ? paddleLeft : paddleRight;
            target.setHeightScale(1.f);
            tinyPaddleActive = false;
        }
    }
}

void PowerUpSystem::update(float dt, std::vector<std::unique_ptr<Ball>>& balls,
                            Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer) {
    trySpawn(dt);
    if (activePowerUp) {
        activePowerUp->update(dt);
    }
    checkCollision(balls, paddleLeft, paddleRight, lastScorer);
    updateEffects(dt, balls, paddleLeft, paddleRight);
}

void PowerUpSystem::draw(sf::RenderWindow& window) {
    if (activePowerUp) {
        activePowerUp->draw(window);
    }
}

bool PowerUpSystem::consumeTwinBallRequest(Ball*& sourceBall) {
    if (!twinBallRequested) return false;
    twinBallRequested = false;
    sourceBall = twinBallSource;
    twinBallSource = nullptr;
    return true;
}