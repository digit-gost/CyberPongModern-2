#include "PowerUpSystem.h"
#include "../core/Game.h"
#include <random>

namespace {
    std::mt19937& rng() {
        static std::mt19937 gen{std::random_device{}()};
        return gen;
    }

    PowerUpType randomType() {
        std::uniform_int_distribution<int> dist(0, 3);
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

void PowerUpSystem::checkCollision(Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer) {
    if (!activePowerUp) return;

    if (ball.getBounds().findIntersection(activePowerUp->getBounds()).has_value()) {
        applyEffect(activePowerUp->getType(), ball, paddleLeft, paddleRight, lastScorer);
        activePowerUp.reset();
    }
}

void PowerUpSystem::applyEffect(PowerUpType type, Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer) {
    switch (type) {
        case PowerUpType::SPEED_BOOST:
            ball.applySpeedMultiplier(1.5f);
            speedBoostActive = true;
            speedBoostTimer = EFFECT_DURATION;
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
            invisibleBallActive = true;
            invisibleBallTimer = INVISIBLE_DURATION;
            break;
    }
}

void PowerUpSystem::updateEffects(float dt, Paddle& paddleLeft, Paddle& paddleRight, Ball& ball) {
    if (speedBoostActive) {
        speedBoostTimer -= dt;
        if (speedBoostTimer <= 0.f) {
            ball.applySpeedMultiplier(1.f / 1.5f);
            speedBoostActive = false;
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

    if (invisibleBallActive) {
        invisibleBallTimer -= dt;
        if (invisibleBallTimer <= 0.f) {
            ball.setVisible(true);
            invisibleBallActive = false;
        }
    }
}

void PowerUpSystem::update(float dt, Ball& ball, Paddle& paddleLeft, Paddle& paddleRight, Paddle::Side lastScorer) {
    trySpawn(dt);
    if (activePowerUp) {
        activePowerUp->update(dt);
    }
    checkCollision(ball, paddleLeft, paddleRight, lastScorer);
    updateEffects(dt, paddleLeft, paddleRight, ball);
}

void PowerUpSystem::draw(sf::RenderWindow& window) {
    if (activePowerUp) {
        activePowerUp->draw(window);
    }
}