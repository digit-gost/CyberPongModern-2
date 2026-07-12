#include "StateGameOver.h"
#include "StateMenu.h"
#include "../core/Game.h"
#include "../core/Paths.h"
#include <memory>
#include <string>

StateGameOver::StateGameOver(Game& game, Paddle::Side winner, int setsLeft, int setsRight)
    : State(game),
      winnerText(game.getAssets().getFont(Assets::FONT_MAIN),
                 winner == Paddle::Side::LEFT ? "CYAN-7 GAGNE !" : "NOVA-X GAGNE !", 52),
      recapText(game.getAssets().getFont(Assets::FONT_MAIN),
                "Sets finaux : CYAN-7  " + std::to_string(setsLeft) + " - " +
                std::to_string(setsRight) + "  NOVA-X", 26),
      hintText(game.getAssets().getFont(Assets::FONT_MAIN), "Entree : retour au menu", 26),
      savedHint(game.getAssets().getFont(Assets::FONT_MAIN),
                "Score enregistre dans les meilleurs scores", 18)
{
    winnerText.setFillColor(winner == Paddle::Side::LEFT ? sf::Color::Cyan : sf::Color::Magenta);
    winnerText.setPosition({280.f, 260.f});

    recapText.setFillColor(sf::Color::White);
    recapText.setPosition({320.f, 330.f});

    hintText.setFillColor(sf::Color::White);
    hintText.setPosition({420.f, 400.f});

    savedHint.setFillColor(sf::Color(160, 160, 160));
    savedHint.setPosition({390.f, 450.f});
}

void StateGameOver::handleEvent(const sf::Event& event) {
    const auto* key = event.getIf<sf::Event::KeyPressed>();
    if (key && key->code == sf::Keyboard::Key::Enter) {
        game.changeState(std::make_unique<StateMenu>(game));
    }
}

void StateGameOver::update(float /*dt*/) {}

void StateGameOver::draw(sf::RenderWindow& window) {
    window.draw(winnerText);
    window.draw(recapText);
    window.draw(hintText);
    window.draw(savedHint);
}