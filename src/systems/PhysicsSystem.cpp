#include "PhysicsSystem.h"
#include <algorithm>
#include <cmath>

void PhysicsSystem::resolveWallCollision(Ball& ball, int screenHeight) {
    sf::FloatRect bounds = ball.getBounds();
    sf::Vector2f vel = ball.getVelocity();

    float top = bounds.position.y;
    float bottom = bounds.position.y + bounds.size.y;

    if (top <= 0.f && vel.y < 0.f) {
        ball.move({0.f, -top});
        ball.setVelocity({vel.x, -vel.y});
    } else if (bottom >= (float)screenHeight && vel.y > 0.f) {
        ball.move({0.f, (float)screenHeight - bottom});
        ball.setVelocity({vel.x, -vel.y});
    }
}

void PhysicsSystem::resolvePaddleCollision(Ball& ball, const Paddle& paddle) {
    sf::FloatRect ballBounds = ball.getBounds();
    sf::FloatRect paddleBounds = paddle.getBounds();

    if (!ballBounds.findIntersection(paddleBounds).has_value()) return;

    // 1. Calculer la position relative d'impact [-1.0 (haut) ... +1.0 (bas)]
    float ballCenterY = ballBounds.position.y + ballBounds.size.y / 2.f;
    float paddleCenterY = paddleBounds.position.y + paddleBounds.size.y / 2.f;
    float relativeHit = (ballCenterY - paddleCenterY) / (paddleBounds.size.y / 2.f);
    relativeHit = std::clamp(relativeHit, -1.f, 1.f);

    // 2. Calculer le nouvel angle (max ±75 degrés)
    float bounceAngle = relativeHit * 75.f * (float)(M_PI / 180.0);

    // 3. Augmenter légèrement la vitesse à chaque échange
    float speed = std::hypot(ball.getVelocity().x, ball.getVelocity().y);
    speed = std::min(speed * SPEED_INCREASE_FACTOR, MAX_BALL_SPEED);

    // 4. Inverser la direction X, appliquer le nouvel angle
    float dirX = (ball.getVelocity().x > 0) ? -1.f : 1.f;
    ball.setVelocity({
        dirX * speed * std::cos(bounceAngle),
        speed * std::sin(bounceAngle)
    });

    // 5. Empêcher la balle de rester dans la raquette (correction de position)
    float correction = paddle.isLeftSide()
        ? paddleBounds.position.x + paddleBounds.size.x - ballBounds.position.x + 1.f
        : paddleBounds.position.x - ballBounds.position.x - ballBounds.size.x - 1.f;
    ball.move({correction, 0.f});

    // NOTE (Jour 3) : émettre ici un événement d'impact (flash visuel, son)
    // via un système Observer, ex. onPaddleHit.emit(paddle.getSide(), relativeHit);
}
