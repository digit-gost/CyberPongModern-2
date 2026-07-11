#include "StateGame.h"
#include "StatePause.h"
#include "StateGameOver.h"
#include "../core/Game.h"
#include "../core/Paths.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>

StateGame::StateGame(Game& game, GameMode mode_)
    : State(game),
      mode(mode_),
      ai(mode_ == GameMode::PVE ? std::make_unique<AIController>(AIDifficulty::CYBORG) : nullptr),
      hud(game.getAssets().getFont(Assets::FONT_MAIN))
{
    ball = std::make_unique<Ball>(sf::Vector2f(Game::WINDOW_W / 2.f, Game::WINDOW_H / 2.f));
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
    sf::FloatRect b = ball->getBounds();

    if (b.position.x + b.size.x < 0.f) {
        scores.addPoint(Paddle::Side::RIGHT);
        ball->reset();
    } else if (b.position.x > Game::WINDOW_W) {
        scores.addPoint(Paddle::Side::LEFT);
        ball->reset();
    }

    if (scores.isMatchOver()) {
        Paddle::Side winner = scores.getMatchWinner();
        std::string label = (winner == Paddle::Side::LEFT) ? "CYAN-7" : "NOVA-X";
        int value = scores.getTotalPoints(winner);
        game.getHighScores().addEntry(label, value);

        game.changeState(std::make_unique<StateGameOver>(game, winner));
    }
}

void StateGame::update(float dt) {
    handlePaddleInput(dt);

    paddleLeft->update(dt);
    paddleRight->update(dt);
    ball->update(dt);

    physics.resolveWallCollision(*ball, Game::WINDOW_H);
    physics.resolvePaddleCollision(*ball, *paddleLeft);
    physics.resolvePaddleCollision(*ball, *paddleRight);

    if (ai) {
        ai->update(*paddleRight, *ball, dt);
    }

    powerups.update(dt, *ball, *paddleLeft, *paddleRight, scores.getLastScorer());

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
    ball->draw(window);
    hud.draw(window);
}