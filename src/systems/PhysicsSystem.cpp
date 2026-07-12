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

bool PhysicsSystem::resolvePaddleCollision(Ball& ball, Paddle& paddle) {
    sf::FloatRect ballBounds = ball.getBounds();
    sf::FloatRect paddleBounds = paddle.getBounds();

    if (!ballBounds.findIntersection(paddleBounds).has_value()) return false;

    float ballCenterY = ballBounds.position.y + ballBounds.size.y / 2.f;
    float paddleCenterY = paddleBounds.position.y + paddleBounds.size.y / 2.f;
    float relativeHit = (ballCenterY - paddleCenterY) / (paddleBounds.size.y / 2.f);
    relativeHit = std::clamp(relativeHit, -1.f, 1.f);

    constexpr float PI = 3.14159265358979323846f;
    float bounceAngle = relativeHit * 75.f * (PI / 180.f);
    float speed = std::hypot(ball.getVelocity().x, ball.getVelocity().y);
    speed = std::min(speed * SPEED_INCREASE_FACTOR, MAX_BALL_SPEED);

    float dirX = (ball.getVelocity().x > 0) ? -1.f : 1.f;
    ball.setVelocity({
        dirX * speed * std::cos(bounceAngle),
        speed * std::sin(bounceAngle)
    });

    float correction = paddle.isLeftSide()
        ? paddleBounds.position.x + paddleBounds.size.x - ballBounds.position.x + 1.f
        : paddleBounds.position.x - ballBounds.position.x - ballBounds.size.x - 1.f;
    ball.move({correction, 0.f});

    paddle.triggerFlash();
    return true;
}