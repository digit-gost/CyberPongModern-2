#include "StateGameOver.h"
#include "StateMenu.h"
#include "../core/Game.h"
#include "../core/AssetManager.h"
#include "../core/Paths.h"
#include <memory>

StateGameOver::StateGameOver(Game& game, Paddle::Side winner)
    : State(game),
      winnerText(game.getAssets().getFont(Assets::FONT_MAIN),
                 winner == Paddle::Side::LEFT ? "CYAN-7 GAGNE !" : "NOVA-X GAGNE !", 52),
      hintText(game.getAssets().getFont(Assets::FONT_MAIN), "Entree : retour au menu", 26)
{
    winnerText.setFillColor(winner == Paddle::Side::LEFT ? sf::Color::Cyan : sf::Color::Magenta);
    winnerText.setPosition({280.f, 280.f});

    hintText.setFillColor(sf::Color::White);
    hintText.setPosition({420.f, 360.f});
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
    window.draw(hintText);
}