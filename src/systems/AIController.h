#pragma once
#include "../entities/Paddle.h"
#include "../entities/Ball.h"

enum class AIDifficulty { ROOKIE, CYBORG, NEXUS9 };

class AIController {
public:
    explicit AIController(AIDifficulty diff);

    void update(Paddle& paddle, const Ball& ball, float dt);
    void setDifficulty(AIDifficulty d) { difficulty = d; }

private:
    AIDifficulty difficulty;

    float getReactionSpeed() const;   // fraction de la vitesse max de la raquette
    float getPredictionError() const; // erreur de prédiction en pixels
    float getReactionDelay() const;   // délai entre 2 recalculs de cible (s)

    float reactionTimer = 0.f;
    float targetY = 0.f;
};