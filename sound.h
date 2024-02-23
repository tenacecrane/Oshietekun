/**
 * @file sound.h
 * @author Michael Sizemore, Kevin Macknight, Jack Gill, Tyson Fox, Ashton Foulger, Tenace Crane, Jacob Pelegrin, Mason Januszewski
 * @brief A8: An Educational App
 * @version 1.0
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 */

#ifndef SOUND_H
#define SOUND_H

#include <QSoundEffect>
#include <QMediaPlayer>
using namespace std;

class Sound : public QObject
{
public:
    Sound();
    QSoundEffect *pronunciation;
    QSoundEffect *BGM;
    QSoundEffect *fireworkPop;
    bool getMuted();

private:
    QSoundEffect effect;
    QMediaPlayer * bgmPlayer = new QMediaPlayer();
    QMediaPlayer * pronunciationPlayer = new QMediaPlayer();
    float volume;
public slots:
    void playSoundEffect(QString);
    void playBGM();
    void muteBGM(bool);
    void playFireworks(QString, bool);
};

#endif // SOUND_H
