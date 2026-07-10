#include "Game.h"
#include "../states/State.h"
#include "../states/StateMenu.h"
#include <optional>

Game::Game()
    : window(sf::VideoMode({(unsigned int)WINDOW_W, (unsigned int)WINDOW_H}),
             "Cyber Pong Modern",
             sf::Style::Titlebar | sf::Style::Close)
{
    window.setFramerateLimit(144);
    changeState(std::make_unique<StateMenu>(*this));
}

Game::~Game() = default;

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (!states.empty()) {
                states.back()->handleEvent(*event);
            }
        }

        if (!states.empty()) {
            states.back()->update(dt);
        }

        window.clear(sf::Color(10, 10, 20));
        for (auto& state : states) {
            state->draw(window);
        }
        window.display();
    }
}

void Game::pushState(std::unique_ptr<State> state) {
    states.push_back(std::move(state));
}

void Game::popState() {
    if (!states.empty()) states.pop_back();
}

void Game::changeState(std::unique_ptr<State> state) {
    states.clear();
    states.push_back(std::move(state));
}