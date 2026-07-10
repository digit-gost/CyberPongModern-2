#pragma once
#include <SFML/Graphics.hpp>

class HUD {
public:
    explicit HUD(sf::Font& font);

    void updateScore(int setsLeft, int pointsLeft, int setsRight, int pointsRight);
    void draw(sf::RenderWindow& window);

private:
    sf::Text labelLeft;       // "CYAN-7   "
    sf::Text pointsLeftText;  // le chiffre, en bleu
    sf::Text separator;       // "   -   "
    sf::Text pointsRightText; // le chiffre, en violet
    sf::Text labelRight;      // "   NOVA-X"
    sf::Text setsLine;        // "Sets : 0 - 0" en dessous

    void layoutScoreLine(); // recalcule la position de chaque morceau
    void centerSetsLine();
};