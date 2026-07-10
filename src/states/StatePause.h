#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>

class StatePause : public State {
public:
    explicit StatePause(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::RectangleShape overlay;
    sf::Text pauseText;
    sf::Text resumeHint;
    sf::Text menuHint;
};