#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "AssetManager.h"
#include "AudioManager.h"
#include "../systems/HighScoreTable.h"

class State;

class Game {
public:
    Game();
    ~Game();

    void run();

    void pushState(std::unique_ptr<State> state);
    void popState();
    void changeState(std::unique_ptr<State> state);

    sf::RenderWindow& getWindow() { return window; }
    AssetManager& getAssets() { return assets; }
    AudioManager& getAudio() { return audio; }
    HighScoreTable& getHighScores() { return highScores; }

    static constexpr int WINDOW_W = 1280;
    static constexpr int WINDOW_H = 720;

private:
    sf::RenderWindow window;
    AssetManager assets;
    AudioManager audio;
    HighScoreTable highScores;
    std::vector<std::unique_ptr<State>> states;

    enum class PendingAction { NONE, PUSH, POP, CHANGE };
    PendingAction pendingAction = PendingAction::NONE;
    std::unique_ptr<State> pendingState;

    void applyPendingStateChange();
};