#include "AIController.h"
#include <random>

namespace {
    std::mt19937& rng() {
        static std::mt19937 gen{std::random_device{}()};
        return gen;
    }
}

AIController::AIController(AIDifficulty diff) : difficulty(diff) {}

float AIController::getReactionSpeed() const {
    switch (difficulty) {
        case AIDifficulty::ROOKIE: return 0.45f;
        case AIDifficulty::CYBORG: return 0.75f;
        case AIDifficulty::NEXUS9: return 1.0f;
    }
    return 1.f;
}

float AIController::getPredictionError() const {
    switch (difficulty) {
        case AIDifficulty::ROOKIE: return 90.f;
        case AIDifficulty::CYBORG: return 35.f;
        case AIDifficulty::NEXUS9: return 6.f;
    }
    return 0.f;
}

float AIController::getReactionDelay() const {
    switch (difficulty) {
        case AIDifficulty::ROOKIE: return 0.35f;
        case AIDifficulty::CYBORG: return 0.15f;
        case AIDifficulty::NEXUS9: return 0.03f;
    }
    return 0.1f;
}

void AIController::update(Paddle& paddle, const Ball& ball, float dt) {
    reactionTimer -= dt;
    if (reactionTimer <= 0.f) {
        std::uniform_real_distribution<float> errorDist(
            -getPredictionError(), getPredictionError());
        targetY = ball.getPosition().y + errorDist(rng());
        reactionTimer = getReactionDelay();
    }

    float currentY = paddle.getPosition().y;
    float diff = targetY - currentY;
    const float deadZone = 5.f;

    if (diff > deadZone) {
        paddle.moveDown(dt * getReactionSpeed());
    } else if (diff < -deadZone) {
        paddle.moveUp(dt * getReactionSpeed());
    }
}