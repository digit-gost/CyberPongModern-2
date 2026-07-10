#include "StatePause.h"
#include "StateMenu.h"
#include "../core/Game.h"
#include "../core/Paths.h"
#include <memory>

StatePause::StatePause(Game& game)
    : State(game),
      pauseText(game.getAssets().getFont(Assets::FONT_MAIN), "PAUSE", 64),
      resumeHint(game.getAssets().getFont(Assets::FONT_MAIN),
                 "P ou Echap : reprendre", 24),
      menuHint(game.getAssets().getFont(Assets::FONT_MAIN),
               "M ou Entree : retour au menu", 24)
{
    overlay.setSize({(float)Game::WINDOW_W, (float)Game::WINDOW_H});
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    pauseText.setFillColor(sf::Color::Cyan);
    pauseText.setPosition({500.f, 280.f});

    resumeHint.setFillColor(sf::Color::White);
    resumeHint.setPosition({430.f, 370.f});

    menuHint.setFillColor(sf::Color::White);
    menuHint.setPosition({380.f, 410.f});
}

void StatePause::handleEvent(const sf::Event& event) {
    const auto* key = event.getIf<sf::Event::KeyPressed>();
    if (!key) return;

    if (key->code == sf::Keyboard::Key::P || key->code == sf::Keyboard::Key::Escape) {
        game.popState();
    } else if (key->code == sf::Keyboard::Key::M || key->code == sf::Keyboard::Key::Enter) {
        game.changeState(std::make_unique<StateMenu>(game));
    }
}

void StatePause::update(float /*dt*/) {}

void StatePause::draw(sf::RenderWindow& window) {
    window.draw(overlay);
    window.draw(pauseText);
    window.draw(resumeHint);
    window.draw(menuHint);
}