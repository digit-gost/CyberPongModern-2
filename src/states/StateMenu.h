#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>

class StateMenu : public State {
public:
    explicit StateMenu(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Text titleText;
    sf::Text optionPVE;
    sf::Text optionPVP;
    sf::Text optionQuit;
    int selectedIndex = 0; // 0 = PVE, 1 = PVP, 2 = Quitter

    void updateSelectionVisuals();
};