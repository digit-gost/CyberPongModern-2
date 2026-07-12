#include "StateGame.h"
#include "StatePause.h"
#include "StateGameOver.h"
#include "../core/Game.h"
#include "../core/Paths.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>

StateGame::StateGame(Game& game, GameMode mode_, AIDifficulty difficulty)
    : State(game),
      mode(mode_),
      ai(mode_ == GameMode::PVE ? std::make_unique<AIController>(difficulty) : nullptr),
      hud(game.getAssets().getFont(Assets::FONT_MAIN))
{
    balls.push_back(std::make_unique<Ball>(sf::Vector2f(Game::WINDOW_W / 2.f, Game::WINDOW_H / 2.f)));
    paddleLeft = std::make_unique<Paddle>(
        sf::Vector2f(40.f, Game::WINDOW_H / 2.f), Paddle::Side::LEFT);
    paddleRight = std::make_unique<Paddle>(
        sf::Vector2f(Game::WINDOW_W - 40.f, Game::WINDOW_H / 2.f), Paddle::Side::RIGHT);
}

void StateGame::handleEvent(const sf::Event& event) {
    const auto* key = event.getIf<sf::Event::KeyPressed>();
    if (!key) return;

    if (key->code == sf::Keyboard::Key::P || key->code == sf::Keyboard::Key::Escape) {
        game.pushState(std::make_unique<StatePause>(game));
    }
}

void StateGame::handlePaddleInput(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        paddleLeft->moveUp(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        paddleLeft->moveDown(dt);
    }

    if (mode == GameMode::PVP) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) paddleRight->moveUp(dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) paddleRight->moveDown(dt);
    }
}

void StateGame::checkScoring() {
    for (size_t i = 0; i < balls.size(); ) {
        sf::FloatRect b = balls[i]->getBounds();
        bool exitedLeft = b.position.x + b.size.x < 0.f;
        bool exitedRight = b.position.x > Game::WINDOW_W;

        if (exitedLeft || exitedRight) {
            Paddle::Side scorer = exitedLeft ? Paddle::Side::RIGHT : Paddle::Side::LEFT;
            scores.addPoint(scorer);

            Paddle::Side setWinner;
            if (scores.consumeSetWin(setWinner)) {
                game.getAudio().playSetWin();
            }

            if (balls.size() > 1) {
                balls.erase(balls.begin() + (long)i);
                continue;
            } else {
                balls[i]->reset();
                ++i;
            }
        } else {
            ++i;
        }
    }

    if (scores.isMatchOver()) {
        Paddle::Side winner = scores.getMatchWinner();
        std::string label = (winner == Paddle::Side::LEFT) ? "CYAN-7" : "NOVA-X";
        int value = scores.getTotalPoints(winner);
        game.getHighScores().addEntry(label, value);

        bool isDefeat = (mode == GameMode::PVE && winner == Paddle::Side::RIGHT);

        game.changeState(std::make_unique<StateGameOver>(
            game, winner,
            scores.getSets(Paddle::Side::LEFT),
            scores.getSets(Paddle::Side::RIGHT),
            isDefeat));
    }
}

void StateGame::update(float dt) {
    handlePaddleInput(dt);

    paddleLeft->update(dt);
    paddleRight->update(dt);

    for (auto& ballPtr : balls) {
        ballPtr->update(dt);
        physics.resolveWallCollision(*ballPtr, Game::WINDOW_H);
        bool hitLeft = physics.resolvePaddleCollision(*ballPtr, *paddleLeft);
        bool hitRight = physics.resolvePaddleCollision(*ballPtr, *paddleRight);
        if (hitLeft || hitRight) {
            game.getAudio().playPaddleHit();
        }
    }
    if (ai && !balls.empty()) {
        ai->update(*paddleRight, *balls[0], dt);
    }

    powerups.update(dt, balls, *paddleLeft, *paddleRight, scores.getLastScorer());

    Ball* twinSource = nullptr;
    if (powerups.consumeTwinBallRequest(twinSource) && twinSource) {
        auto twin = std::make_unique<Ball>(twinSource->getPosition());
        twin->setVelocity({-twinSource->getVelocity().x, twinSource->getVelocity().y});
        balls.push_back(std::move(twin));
    }

    checkScoring();

    hud.updateScore(scores.getSets(Paddle::Side::LEFT), scores.getSetPoints(Paddle::Side::LEFT),
                     scores.getSets(Paddle::Side::RIGHT), scores.getSetPoints(Paddle::Side::RIGHT));

    gridOffset += 60.f * dt;
    if (gridOffset > GRID_CELL) gridOffset -= GRID_CELL;
}

void StateGame::drawCyberGrid(sf::RenderWindow& window) {
    const int W = Game::WINDOW_W;
    const int H = Game::WINDOW_H;
    sf::Color lineColor(0, 255, 255, 35);

    for (int y = (int)gridOffset % GRID_CELL; y < H + GRID_CELL; y += GRID_CELL) {
        float alpha = 20.f + 40.f * ((float)y / H);
        lineColor.a = (std::uint8_t)alpha;
        sf::Vertex line[] = {
            {{0.f, (float)y}, lineColor},
            {{(float)W, (float)y}, lineColor}
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    const int VLINES = 16;
    for (int i = 0; i <= VLINES; ++i) {
        float topX = (float)W / VLINES * i;
        float botX = (float)W / 2.f + (topX - W / 2.f) * 1.5f;
        botX = std::clamp(botX, 0.f, (float)W);
        sf::Vertex vline[] = {
            {{topX, 0.f}, sf::Color(0, 255, 255, 15)},
            {{botX, (float)H}, sf::Color(0, 255, 255, 50)}
        };
        window.draw(vline, 2, sf::PrimitiveType::Lines);
    }
}

void StateGame::draw(sf::RenderWindow& window) {
    drawCyberGrid(window);
    powerups.draw(window);
    paddleLeft->draw(window);
    paddleRight->draw(window);
    for (auto& ballPtr : balls) {
        ballPtr->draw(window);
    }
    hud.draw(window);
}