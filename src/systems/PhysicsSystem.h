#pragma once
#include "../entities/Ball.h"
#include "../entities/Paddle.h"

class PhysicsSystem {
public:
    void resolveWallCollision(Ball& ball, int screenHeight);

    // Retourne true si une collision a ete resolue (utile pour jouer un son)
    bool resolvePaddleCollision(Ball& ball, Paddle& paddle);

    static constexpr float SPEED_INCREASE_FACTOR = 1.05f;
    static constexpr float MAX_BALL_SPEED = 900.f;
};