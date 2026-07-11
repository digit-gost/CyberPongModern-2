#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "AssetManager.h"
#include "../systems/HighScoreTable.h"

class State;

class Game {
public:
    Game();
    ~Game();

    void run();

    // Ces méthodes ne font QUE noter la demande ; le changement réel est
    // appliqué en fin de frame (voir applyPendingStateChange), pour ne
    // jamais détruire un State pendant qu'il est en train de s'exécuter.
    void pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state);

    sf::RenderWindow& getWindow() { return window; }
    AssetManager& getAssets() { return assets; }
    HighScoreTable& getHighScores() { return highScores; }

    static constexpr int WINDOW_W = 1280;
    static constexpr int WINDOW_H = 720;

private:
    sf::RenderWindow window;
    AssetManager assets;
    HighScoreTable highScores;
    std::vector<std::unique_ptr<State>> states;

    enum class PendingAction { NONE, PUSH, POP, CHANGE };
    PendingAction pendingAction = PendingAction::NONE;
    std::unique_ptr<State> pendingState;

    void applyPendingStateChange();
};