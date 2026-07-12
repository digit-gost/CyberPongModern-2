#pragma once
#include "State.h"
#include "GameMode.h"
#include "../entities/Ball.h"
#include "../entities/Paddle.h"
#include "../systems/PhysicsSystem.h"
#include "../systems/AIController.h"
#include "../systems/ScoreSystem.h"
#include "../systems/PowerUpSystem.h"
#include "../ui/HUD.h"
#include <memory>
#include <vector>

class StateGame : public State {
public:
    StateGame(Game& game, GameMode mode, AIDifficulty difficulty = AIDifficulty::CYBORG);
    
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    GameMode mode;
    std::vector<std::unique_ptr<Ball>> balls; // balls[0] = balle principale
    std::unique_ptr<Paddle> paddleLeft;
    std::unique_ptr<Paddle> paddleRight;
    std::unique_ptr<AIController> ai;
    PhysicsSystem physics;
    ScoreSystem scores;
    PowerUpSystem powerups;
    HUD hud;

    float gridOffset = 0.f;
    static constexpr int GRID_CELL = 80;

    void handlePaddleInput(float dt);
    void checkScoring();
    void drawCyberGrid(sf::RenderWindow& window);
};