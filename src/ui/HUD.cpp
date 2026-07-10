#include "HUD.h"
#include "../core/Game.h"
#include <string>

HUD::HUD(sf::Font& font)
    : labelLeft(font, "CYAN-7   ", 34),
      pointsLeftText(font, "0", 34),
      separator(font, "   -   ", 34),
      pointsRightText(font, "0", 34),
      labelRight(font, "   NOVA-X", 34),
      setsLine(font, "Sets : 0 - 0", 18)
{
    labelLeft.setFillColor(sf::Color::White);
    pointsLeftText.setFillColor(sf::Color(30, 144, 255));   // bleu
    separator.setFillColor(sf::Color::White);
    pointsRightText.setFillColor(sf::Color(148, 0, 211));   // violet
    labelRight.setFillColor(sf::Color::White);
    setsLine.setFillColor(sf::Color(200, 200, 200));

    layoutScoreLine();
    centerSetsLine();
}

void HUD::layoutScoreLine() {
    sf::Text* parts[5] = {&labelLeft, &pointsLeftText, &separator, &pointsRightText, &labelRight};

    float totalWidth = 0.f;
    for (auto* t : parts) {
        totalWidth += t->getLocalBounds().size.x;
    }

    float x = Game::WINDOW_W / 2.f - totalWidth / 2.f;
    const float y = 15.f;

    for (auto* t : parts) {
        sf::FloatRect b = t->getLocalBounds();
        t->setPosition({x - b.position.x, y - b.position.y});
        x += b.size.x;
    }
}

void HUD::centerSetsLine() {
    sf::FloatRect b = setsLine.getLocalBounds();
    setsLine.setOrigin({b.position.x + b.size.x / 2.f, b.position.y});
    setsLine.setPosition({Game::WINDOW_W / 2.f, 55.f});
}

void HUD::updateScore(int setsLeft, int pointsLeft, int setsRight, int pointsRight) {
    pointsLeftText.setString(std::to_string(pointsLeft));
    pointsRightText.setString(std::to_string(pointsRight));
    setsLine.setString("Sets : " + std::to_string(setsLeft) + " - " + std::to_string(setsRight));

    layoutScoreLine(); // les chiffres changent de largeur (1 vs 10), on recentre tout
    centerSetsLine();
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(labelLeft);
    window.draw(pointsLeftText);
    window.draw(separator);
    window.draw(pointsRightText);
    window.draw(labelRight);
    window.draw(setsLine);
}