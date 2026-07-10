#include "StateMenu.h"
#include "StateGame.h"
#include "GameMode.h"
#include "../core/Game.h"
#include "../core/AssetManager.h"
#include "../core/Paths.h"
#include <memory>

StateMenu::StateMenu(Game& game)
    : State(game),
      titleText(game.getAssets().getFont(Assets::FONT_MAIN), "CYBER PONG MODERN", 56),
      optionPVE(game.getAssets().getFont(Assets::FONT_MAIN), "Jouer (1P vs IA)", 32),
      optionPVP(game.getAssets().getFont(Assets::FONT_MAIN), "Duel (2P)", 32),
      optionQuit(game.getAssets().getFont(Assets::FONT_MAIN), "Quitter", 32)
{
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setPosition({260.f, 100.f});

    optionPVE.setPosition({520.f, 300.f});
    optionPVP.setPosition({520.f, 370.f});
    optionQuit.setPosition({520.f, 440.f});

    updateSelectionVisuals();
}

void StateMenu::updateSelectionVisuals() {
    sf::Text* options[3] = {&optionPVE, &optionPVP, &optionQuit};
    for (int i = 0; i < 3; ++i) {
        options[i]->setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
    }
}

void StateMenu::handleEvent(const sf::Event& event) {
    const auto* key = event.getIf<sf::Event::KeyPressed>();
    if (!key) return;

    if (key->code == sf::Keyboard::Key::Up) {
        selectedIndex = (selectedIndex + 2) % 3;
        updateSelectionVisuals();
    } else if (key->code == sf::Keyboard::Key::Down) {
        selectedIndex = (selectedIndex + 1) % 3;
        updateSelectionVisuals();
    } else if (key->code == sf::Keyboard::Key::Enter) {
        if (selectedIndex == 0) {
            game.changeState(std::make_unique<StateGame>(game, GameMode::PVE));
        } else if (selectedIndex == 1) {
            game.changeState(std::make_unique<StateGame>(game, GameMode::PVP));
        } else {
            game.getWindow().close();
        }
    } else if (key->code == sf::Keyboard::Key::Escape) {
        game.getWindow().close();
    }
}

void StateMenu::update(float /*dt*/) {}

void StateMenu::draw(sf::RenderWindow& window) {
    window.draw(titleText);
    window.draw(optionPVE);
    window.draw(optionPVP);
    window.draw(optionQuit);
}