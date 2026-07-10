#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

// Cache de polices — un objet normal possédé par Game (pas de variable
// statique), pour éviter les problèmes d'ordre de destruction avec les
// ressources internes de SFML au moment de la fermeture du programme.
class AssetManager {
public:
    sf::Font& getFont(const std::string& path);

private:
    std::unordered_map<std::string, sf::Font> fonts;
};