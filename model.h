#ifndef MODEL_H
#define MODEL_H

#include "QVector"
#include "level.h"
#include "character.h"
#include <QSoundEffect>
#include <QRandomGenerator>
#include <QFile>
#include <fstream>
#include <QElapsedTimer>


class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void initiateLevel(int selectedLevel);
    void receiveSelectionOne(int);
    void receiveSelectionTwo(int);
    void getKanaImage(int);
    void recieveMatch(bool);
    void sendLevelData();

private:
    const int hiraganaOffset = 46;
    const int katakanaOffset = 92;
    QVector<int> hiraganaSet;
    QVector<int> katakanaSet;
    QVector<int> combinedSet;
    QVector<Level> practiceLevels;
    Character japaneseCharacters[46];
    Level hiraganaLvl1;
    Level hiraganaLvl2;
    Level hiraganaLvl3;
    Level hiraganaLvl4;
    Level hiraganaLvl5;
    Level hiraganaLvl6;
    Level katakanaLvl1;
    Level katakanaLvl2;
    Level katakanaLvl3;
    Level katakanaLvl4;
    Level katakanaLvl5;
    Level katakanaLvl6;
    Level combinedLvl1;
    Level combinedLvl2;
    Level combinedLvl3;
    Level combinedLvl4;
    Level combinedLvl5;
    Level combinedLvl6;
    QVector<int> randomizedLevel;
    void populateCharacters();
    void populateLevels();
    void insertCharacter(int givenCharacter);
    void clearCharacterSets();
    int selectionOne;
    void setUpConfig();
    void saveFile();
    void loadFile();
    string BoolToString(bool);
    int matches;
    Level *currentLevel;
    int mistakes;
    QElapsedTimer timer;

signals:
    void sendLevels(QVector<Character>,int);
    void sendMatch(bool);
    void sendKanaImage(QString);
    void updateLevel();
    void updateTimeLabel(int);
    void loadCompletion(QVector<Level>);
};

#endif // MODEL_H
