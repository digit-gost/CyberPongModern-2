#pragma once
#include "../entities/Paddle.h"
#include "../entities/Ball.h"

enum class AIDifficulty { ROOKIE, CYBORG, NEXUS9 };

inline const char* toString(AIDifficulty d) {
    switch (d) {
        case AIDifficulty::ROOKIE: return "Rookie";
        case AIDifficulty::CYBORG: return "Cyborg";
        case AIDifficulty::NEXUS9: return "NEXUS-9";
    }
    return "?";
}

class AIController {
public:
    explicit AIController(AIDifficulty diff);

    void update(Paddle& paddle, const Ball& ball, float dt);
    void setDifficulty(AIDifficulty d) { difficulty = d; }

private:
    AIDifficulty difficulty;

    float getReactionSpeed() const;
    float getPredictionError() const;
    float getReactionDelay() const;

    float reactionTimer = 0.f;
    float targetY = 0.f;
};