#include "StateMenu.h"
#include "StateGame.h"
#include "GameMode.h"
#include "../core/Game.h"
#include "../core/Paths.h"
#include "../systems/HighScoreTable.h"
#include <memory>
#include <string>

StateMenu::StateMenu(Game& game)
    : State(game),
      titleText(game.getAssets().getFont(Assets::FONT_MAIN), "CYBER PONG MODERN", 56),
      optionPVE(game.getAssets().getFont(Assets::FONT_MAIN), "Jouer (1P vs IA)", 32),
      optionPVP(game.getAssets().getFont(Assets::FONT_MAIN), "Duel (2P)", 32),
      optionScores(game.getAssets().getFont(Assets::FONT_MAIN), "Meilleurs scores", 32),
      optionQuit(game.getAssets().getFont(Assets::FONT_MAIN), "Quitter", 32),
      scoresListText(game.getAssets().getFont(Assets::FONT_MAIN), "", 28),
      backHint(game.getAssets().getFont(Assets::FONT_MAIN), "Echap ou Entree : retour", 20)
{
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setPosition({260.f, 90.f});

    optionPVE.setPosition({520.f, 280.f});
    optionPVP.setPosition({520.f, 340.f});
    optionScores.setPosition({520.f, 400.f});
    optionQuit.setPosition({520.f, 460.f});

    scoresListText.setFillColor(sf::Color::White);
    scoresListText.setPosition({480.f, 250.f});

    backHint.setFillColor(sf::Color(180, 180, 180));
    backHint.setPosition({430.f, 560.f});

    updateSelectionVisuals();
}

void StateMenu::updateSelectionVisuals() {
    sf::Text* options[4] = {&optionPVE, &optionPVP, &optionScores, &optionQuit};
    for (int i = 0; i < 4; ++i) {
        options[i]->setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
    }
}

void StateMenu::buildScoresList() {
    const auto& entries = game.getHighScores().getEntries();

    std::string content = "TOP 5\n\n";
    if (entries.empty()) {
        content += "Aucun score enregistre pour l'instant.";
    } else {
        int rank = 1;
        for (const auto& e : entries) {
            content += std::to_string(rank) + ". " + e.label + "  -  " + std::to_string(e.score) + " pts\n";
            rank++;
        }
    }
    scoresListText.setString(content);
}

void StateMenu::handleEvent(const sf::Event& event) {
    const auto* key = event.getIf<sf::Event::KeyPressed>();
    if (!key) return;

    if (showingScores) {
        if (key->code == sf::Keyboard::Key::Escape || key->code == sf::Keyboard::Key::Enter) {
            showingScores = false;
        }
        return;
    }

    if (key->code == sf::Keyboard::Key::Up) {
        selectedIndex = (selectedIndex + 3) % 4;
        updateSelectionVisuals();
    } else if (key->code == sf::Keyboard::Key::Down) {
        selectedIndex = (selectedIndex + 1) % 4;
        updateSelectionVisuals();
    } else if (key->code == sf::Keyboard::Key::Enter) {
        if (selectedIndex == 0) {
            game.changeState(std::make_unique<StateGame>(game, GameMode::PVE));
        } else if (selectedIndex == 1) {
            game.changeState(std::make_unique<StateGame>(game, GameMode::PVP));
        } else if (selectedIndex == 2) {
            buildScoresList();
            showingScores = true;
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

    if (showingScores) {
        window.draw(scoresListText);
        window.draw(backHint);
    } else {
        window.draw(optionPVE);
        window.draw(optionPVP);
        window.draw(optionScores);
        window.draw(optionQuit);
    }
}