#include "AudioManager.h"
#include "Paths.h"
#include <iostream>

AudioManager::AudioManager()
    : hitSound(hitBuffer), victorySound(victoryBuffer)
{
    if (!hitBuffer.loadFromFile(Assets::SOUND_PADDLE_HIT)) {
        std::cerr << "[AudioManager] Impossible de charger : "
                  << Assets::SOUND_PADDLE_HIT << std::endl;
    } else {
        hitLoaded = true;
    }

    if (!victoryBuffer.loadFromFile(Assets::SOUND_VICTORY)) {
        std::cerr << "[AudioManager] Impossible de charger : "
                  << Assets::SOUND_VICTORY << std::endl;
    } else {
        victoryLoaded = true;
    }

    if (!music.openFromFile(Assets::MUSIC_AMBIANCE)) {
        std::cerr << "[AudioManager] Impossible de charger : "
                  << Assets::MUSIC_AMBIANCE << std::endl;
    } else {
        musicLoaded = true;
        music.setLooping(true);
        music.setVolume(35.f); // discret, ne doit pas couvrir les effets
    }
}

void AudioManager::playPaddleHit() {
    if (hitLoaded) hitSound.play();
}

void AudioManager::playVictory() {
    if (victoryLoaded) victorySound.play();
}

void AudioManager::startMusic() {
    if (musicLoaded && music.getStatus() != sf::SoundSource::Status::Playing) {
        music.play();
    }
}

void AudioManager::stopMusic() {
    if (musicLoaded) music.stop();
}