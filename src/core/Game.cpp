#include "Game.h"

Game::Game()
    : window(sf::VideoMode({(unsigned int)WINDOW_W, (unsigned int)WINDOW_H}),
             "Cyber Pong Modern",
             sf::Style::Titlebar | sf::Style::Close)
{
    window.setFramerateLimit(144); // le jeu doit rester correct à 30 et 144 FPS grâce au dt

    ball = std::make_unique<Ball>(sf::Vector2f(WINDOW_W / 2.f, WINDOW_H / 2.f));
    paddleLeft = std::make_unique<Paddle>(
        sf::Vector2f(40.f, WINDOW_H / 2.f), Paddle::Side::LEFT);
    paddleRight = std::make_unique<Paddle>(
        sf::Vector2f(WINDOW_W - 40.f, WINDOW_H / 2.f), Paddle::Side::RIGHT);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Escape) {
                window.close();
            }
        }
    }
}

void Game::handlePaddleInput(float dt) {
    // Joueur gauche : Z / S (clavier AZERTY) — adapter W/S si QWERTY
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        paddleLeft->moveUp(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        paddleLeft->moveDown(dt);
    }

    // Joueur droit : flèches Haut/Bas
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        paddleRight->moveUp(dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        paddleRight->moveDown(dt);
    }
}

void Game::update(float dt) {
    handlePaddleInput(dt);

    paddleLeft->update(dt);
    paddleRight->update(dt);
    ball->update(dt);

    physics.resolveWallCollision(*ball, WINDOW_H);
    physics.resolvePaddleCollision(*ball, *paddleLeft);
    physics.resolvePaddleCollision(*ball, *paddleRight);

    // Sortie de terrain gauche/droite -> reset simple pour l'instant
    // (le score arrive au Jour 2 avec ScoreSystem)
    sf::FloatRect b = ball->getBounds();
    if (b.position.x + b.size.x < 0.f || b.position.x > WINDOW_W) {
        ball->reset();
    }
}

void Game::render() {
    window.clear(sf::Color(10, 10, 20)); // fond sombre cyberpunk provisoire

    paddleLeft->draw(window);
    paddleRight->draw(window);
    ball->draw(window);

    window.display();
}
