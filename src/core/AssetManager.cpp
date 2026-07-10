#include "AssetManager.h"
#include <iostream>

sf::Font& AssetManager::getFont(const std::string& path) {
    auto found = fonts.find(path);
    if (found != fonts.end()) {
        return found->second;
    }

    sf::Font font;
    if (!font.openFromFile(path)) {
        std::cerr << "[AssetManager] Impossible de charger la police : "
                  << path << std::endl;
    }

    auto [it, inserted] = fonts.emplace(path, std::move(font));
    (void)inserted;
    return it->second;
}