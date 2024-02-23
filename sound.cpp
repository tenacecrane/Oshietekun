/**
 * @file sound.cpp
 * @author Michael Sizemore, Kevin Macknight, Jack Gill, Tyson Fox, Ashton Foulger, Tenace Crane, Jacob Pelegrin, Mason Januszewski
 * @brief A8: An Educational App
 * @version 1.0
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 */

#include "sound.h"
#include <iostream>

/**
 * @brief Sound::Sound Sound class initializer.
 */
Sound::Sound()
{
    volume = 0.60;
    BGM = new QSoundEffect();
    pronunciation = new QSoundEffect();
}

/**
 * @brief Sound::playSoundEffect plays the given sound effect.
 * @param soundPrefix the sound effect filename
 */
void Sound::playSoundEffect(QString soundPrefix){
    pronunciation->setSource(QUrl::fromLocalFile(":/sounds/sounds/" + soundPrefix + ".wav"));
    pronunciation->setVolume(0.90);
    pronunciation->setLoopCount(1);
    pronunciation->play();
}

/**
 * @brief Sound::playFireworks Plays the
 * sound effect for the fireworks.
 * @param fireworksound the fireworks wav file
 * name in the sound file.
 * @param mute Determines if the sound effect should play or not.
 */
void Sound::playFireworks(QString fireworksound, bool mute){
    if(!mute){
        fireworkPop = new QSoundEffect(this);
        fireworkPop->setSource(QUrl::fromLocalFile(":/sounds/sounds/" + fireworksound + ".wav"));
        fireworkPop->setVolume(0.90);
        fireworkPop->setLoopCount(1);
        fireworkPop->play();
    }
}

/**
 * @brief Sound::playBGM Plays the background music.
 */
void Sound::playBGM(){
    BGM->setSource(QUrl::fromLocalFile(":/sounds/sounds/JapaneseBGM.wav"));
    BGM->setVolume(0.60);
    BGM->setLoopCount(QSoundEffect::Infinite);
    BGM->play();
}

/**
 * @brief Sound::muteBGM Mutes the sound if already
 * unmuted, or unmutes the sound if already muted.
 * @param mute bool to determine if the sound should
 * be muted or not.
 */
void Sound::muteBGM(bool mute){
    if(mute) {
        BGM->setMuted(true);
        pronunciation->setMuted(true);
    }
    else {
        BGM->setMuted(false);
        pronunciation->setMuted(false);
    }
}

/**
 * @brief Sound::getMuted helper that returns
 * if the sound should be muted.
 * @return if the sound should be muted or not via bool.
 */
bool Sound::getMuted(){
    return BGM->isMuted();
}
