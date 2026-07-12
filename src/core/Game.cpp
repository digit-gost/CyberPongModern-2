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
    highScores.load();
    audio.startMusic();
    changeState(std::make_unique<StateMenu>(*this));
    applyPendingStateChange();
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

        applyPendingStateChange();

        window.clear(sf::Color(10, 10, 20));
        for (auto& state : states) {
            state->draw(window);
        }
        window.display();
    }
}

void Game::pushState(std::unique_ptr<State> state) {
    pendingAction = PendingAction::PUSH;
    pendingState = std::move(state);
}

void Game::popState() {
    pendingAction = PendingAction::POP;
}

void Game::changeState(std::unique_ptr<State> state) {
    pendingAction = PendingAction::CHANGE;
    pendingState = std::move(state);
}

void Game::applyPendingStateChange() {
    switch (pendingAction) {
        case PendingAction::PUSH:
            states.push_back(std::move(pendingState));
            break;
        case PendingAction::POP:
            if (!states.empty()) states.pop_back();
            break;
        case PendingAction::CHANGE:
            states.clear();
            states.push_back(std::move(pendingState));
            break;
        case PendingAction::NONE:
            break;
    }
    pendingAction = PendingAction::NONE;
}