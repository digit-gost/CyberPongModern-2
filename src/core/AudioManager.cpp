#include "AudioManager.h"
#include "Paths.h"
#include <iostream>

AudioManager::AudioManager()
    : hitSound(hitBuffer),
      victorySound(victoryBuffer),
      defeatSound(defeatBuffer),
      setWinSound(setWinBuffer)
{
    if (!hitBuffer.loadFromFile(Assets::SOUND_PADDLE_HIT)) {
        std::cerr << "[AudioManager] Impossible de charger : " << Assets::SOUND_PADDLE_HIT << std::endl;
    } else {
        hitLoaded = true;
    }

    if (!victoryBuffer.loadFromFile(Assets::SOUND_VICTORY)) {
        std::cerr << "[AudioManager] Impossible de charger : " << Assets::SOUND_VICTORY << std::endl;
    } else {
        victoryLoaded = true;
    }

    if (!defeatBuffer.loadFromFile(Assets::SOUND_DEFEAT)) {
        std::cerr << "[AudioManager] Impossible de charger : " << Assets::SOUND_DEFEAT << std::endl;
    } else {
        defeatLoaded = true;
    }

    if (!setWinBuffer.loadFromFile(Assets::SOUND_SET_WIN)) {
        std::cerr << "[AudioManager] Impossible de charger : " << Assets::SOUND_SET_WIN << std::endl;
    } else {
        setWinLoaded = true;
    }

    if (!music.openFromFile(Assets::MUSIC_AMBIANCE)) {
        std::cerr << "[AudioManager] Impossible de charger : " << Assets::MUSIC_AMBIANCE << std::endl;
    } else {
        musicLoaded = true;
        music.setLooping(true);
        music.setVolume(35.f);
    }
}

void AudioManager::playPaddleHit() {
    if (hitLoaded) hitSound.play();
}

void AudioManager::playVictory() {
    if (victoryLoaded) victorySound.play();
}

void AudioManager::playDefeat() {
    if (defeatLoaded) defeatSound.play();
}

void AudioManager::playSetWin() {
    if (setWinLoaded) setWinSound.play();
}

void AudioManager::startMusic() {
    if (musicLoaded && music.getStatus() != sf::SoundSource::Status::Playing) {
        music.play();
    }
}

void AudioManager::stopMusic() {
    if (musicLoaded) music.stop();
}