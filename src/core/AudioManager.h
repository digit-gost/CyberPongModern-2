#pragma once
#include <SFML/Audio.hpp>

class AudioManager {
public:
    AudioManager();

    void playPaddleHit();
    void playVictory();
    void playDefeat();
    void playSetWin();
    void startMusic();
    void stopMusic();

private:
    sf::SoundBuffer hitBuffer;
    sf::SoundBuffer victoryBuffer;
    sf::SoundBuffer defeatBuffer;
    sf::SoundBuffer setWinBuffer;

    sf::Sound hitSound;
    sf::Sound victorySound;
    sf::Sound defeatSound;
    sf::Sound setWinSound;

    sf::Music music;

    bool hitLoaded = false;
    bool victoryLoaded = false;
    bool defeatLoaded = false;
    bool setWinLoaded = false;
    bool musicLoaded = false;
};