#pragma once
#include "State.h"
#include "../entities/Paddle.h"
#include <SFML/Graphics.hpp>

class StateGameOver : public State {
public:
    StateGameOver(Game& game, Paddle::Side winner, int setsLeft, int setsRight, bool isDefeat);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text winnerText;
    sf::Text recapText;
    sf::Text hintText;
    sf::Text savedHint;
};