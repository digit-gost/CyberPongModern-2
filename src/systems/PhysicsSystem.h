#pragma once
#include "../entities/Ball.h"
#include "../entities/Paddle.h"

class PhysicsSystem {
public:
    // Rebond sur les bords haut/bas de l'écran
    void resolveWallCollision(Ball& ball, int screenHeight);

    // Rebond sur une raquette : angle selon le point d'impact + accélération
    void resolvePaddleCollision(Ball& ball, const Paddle& paddle);

    static constexpr float SPEED_INCREASE_FACTOR = 1.05f; // +5% par échange
    static constexpr float MAX_BALL_SPEED = 900.f;        // pixels/seconde
};
