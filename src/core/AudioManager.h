#pragma once
#include <SFML/Audio.hpp>

// Gere les effets sonores et la musique d'ambiance. Possede directement
// ses SoundBuffer et sf::Music (pas de static), pour eviter tout probleme
// d'ordre de destruction (meme logique que AssetManager).
class AudioManager {
public:
    AudioManager();

    void playPaddleHit();
    void playVictory();
    void startMusic();
    void stopMusic();

private:
    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer victoryBuffer;
    sf::Sound hitSound;
    sf::Sound victorySound;
    sf::Music music;

    bool hitLoaded = false;
    bool victoryLoaded = false;
    bool musicLoaded = false;
};