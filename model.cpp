/**
 * @file model.cpp
 * @author Michael Sizemore, Kevin Macknight, Jack Gill, Tyson Fox, Ashton Foulger, Tenace Crane, Jacob Pelegrin, Mason Januszewski
 * @brief A8: An Educational App
 * @version 1.0
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 */
#include "model.h"
#include "qdebug.h"
#include <iostream>
/**
 *
 * @brief Model::Model
 * constructor
 * @param parent
 */
Model::Model(QObject *parent) : QObject{parent}
{
    populateCharacters();
    populateLevels();
    setUpConfig();
}

/**
 * @brief Model::populateCharacters
 * sets up the array of characters that will be used in the game levels
 */
void Model::populateCharacters(){
    string kanaBase[5] = {"a", "i", "u", "e", "o"};
    string kanaModifier[10] = {"", "k", "s", "t", "n", "h", "m", "y", "r", "w"};
    string kanaUnique[4] = {"shi", "chi", "tsu", "fu"};
    string specialCases[4] = {"si", "ti", "tu", "hu"};
    string skipCases[5] = {"yi", "ye", "wi", "wu", "we"};
    string hiraganaURL = ":/images/characters/hiragana_";
    string katakanaURL = ":/images/characters/katakana_";
    int characterCount = 0;
    int uniqueCount = 0;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 5; j++){
            string currentKana = (kanaModifier[i]) + (kanaBase[j]);
            if (find(begin(specialCases), end(specialCases), currentKana) != end(specialCases))
                currentKana = kanaUnique[uniqueCount++];
            if(characterCount < 46 && !(find(begin(skipCases), end(skipCases), currentKana) != end(skipCases))){
                japaneseCharacters[characterCount] = Character(characterCount,currentKana, hiraganaURL + currentKana + ".png", katakanaURL + currentKana + ".png");
                characterCount++;
            }
        }
    }
    japaneseCharacters[45] = Character(45,"n", ":/images/characters/hiragana_n.png", ":/images/characters/katakana_n.png");
}

/**
 * @brief Model::createLevels creates all the levels for practice use.
 * A QVector is created to hold each set of characters for the
 * specific level.
 */
void Model::populateLevels(){
    for (int i = 1; i <= 18; i++){
        Level *insertedLevel= new Level();
        if(i%5==0){
            insertedLevel->LevelSize=6;
        }else
        {
            insertedLevel->LevelSize=10;
        }
        practiceLevels.push_back(*insertedLevel);
    }
}

/**
 * @brief Model::insertCharacter is a helper method for populateLevels.
 * It takes a given character and adds the romaji, katakana, and hiragana
 * to each QVector that it belongs to. Since there are 46 kana characters
 * for each set, and they're stored in the same vector, the hiragana and
 * katakana offsets for indexing are 46 and 92 respectively.
 * @param givenCharacter - The character for which the romaji, hiragana,
 * and katakana are added to the level for.
 */
void Model::insertCharacter(int givenCharacter){
    hiraganaSet.append(givenCharacter);
    hiraganaSet.append(givenCharacter+hiraganaOffset);
    katakanaSet.append(givenCharacter);
    katakanaSet.append(givenCharacter+katakanaOffset);
    combinedSet.append(givenCharacter+hiraganaOffset);
    combinedSet.append(givenCharacter+katakanaOffset);
}

/**
 * @brief Model::clearCharacterSets is a helper method for populateLevels.
 * After a set of similar levels have been populated, the character sets
 * are cleared in preparation for the next set of levels.
 */
void Model::clearCharacterSets(){
    hiraganaSet.clear();
    katakanaSet.clear();
    combinedSet.clear();
}

/**
 * @brief Model::initiateLevel is a slot that takes in a desired level
 * of a QPushButton in the levelSelect page of the UI. This method handles
 * the randomization of a level's characters, as well as the population of
 * the character's QPushButtons in the view through a signal to the MainWindow.
 * @param selectedLevel - the level to be randomized and populated to the UI.
 */
void Model::initiateLevel(int selectedLevel){
    //There are 18 levels.
    //Starting index at 1.

    QVector<Character> emitedVector;
    currentLevel=&practiceLevels[selectedLevel];
    emit updateTimeLabel(currentLevel->getBestTime());
    matches=0;
    mistakes=0;
    timer.restart();

    switch(selectedLevel%6){
    case 0:
        for(int i=0;i<10;i++){
            emitedVector.append(japaneseCharacters[i]);
        }
        break;
    case 1:
        for(int i = 10; i < 20; i++){
            emitedVector.append(japaneseCharacters[i]);
        }
        break;
    case 2:
        for(int i = 20; i < 30; i++){
            emitedVector.append(japaneseCharacters[i]);
        }
        break;
    case 3:
        for(int i = 30; i < 43; i++){
            if(i > 34 && i < 38)
                continue;
            emitedVector.append(japaneseCharacters[i]);
        }
        break;
    case 4:
        for(int i = 35; i < 46; i++){
            if(i > 37 && i < 43)
                continue;
            emitedVector.append(japaneseCharacters[i]);

        }
        break;
    case 5:
        std::vector<Character> tempVector;
        for(int i = 0; i < 46; i++)
            tempVector.push_back(japaneseCharacters[i]);

        std::random_shuffle(std::begin(tempVector), std::end(tempVector));
        for(int i=0;i<10;i++){
            emitedVector.append(tempVector[i]);
        }
        break;
    }
    emit sendLevels(emitedVector,selectedLevel);
}
/**
 * @brief Model::receiveSelectionOne
 * helper method for the first selection of the level
 * @param i
 * the selected buttons index
 */
void Model::receiveSelectionOne(int i){
    selectionOne=i;
}
/**
 * @brief Model::receiveSelectionTwo
 * method that recieves the second selection and compares it with the first to see if they match
 * @param i
 * the second selected buttons index
 */
void Model::receiveSelectionTwo(int i){
    if(selectionOne%46==i%46){
        emit sendMatch(true);
    }
    else{
        emit sendMatch(false);
    }
}
/**
 * @brief Model::getKanaImage
 * gets the image for the index of the input value
 * @param i
 * the index from 0 to 91 of images to find
 */
void Model::getKanaImage(int i){
    QString filePath;
    if(i/46 == 0)
        filePath = QString::fromStdString(japaneseCharacters[i%46].getHiragana());
    else
        filePath = QString::fromStdString(japaneseCharacters[i%46].getKatakana());
    emit sendKanaImage(filePath);
}
/**
 * @brief Model::setUpConfig
 * basic set up for the config file
 */
void Model::setUpConfig(){
    QFile file("config.txt");
    if(!file.exists()){
        file.flush();
        file.close();
        saveFile();
    }
    else{
        loadFile();
    }
}

/**
 * @brief Model::saveFile
 * saves the players data to a config text file
 */
void Model::saveFile(){
    QFile givenFile("config.txt");
    QByteArray indent = "       ";
    if(givenFile.open(QIODevice::ReadWrite | QIODevice::Text)){
        givenFile.write(QByteArray("{ \n"));
        givenFile.write(QByteArray(indent + "\"levels\": { \n"));
        givenFile.write(QByteArray());
        for(int i = 0; i < (int) practiceLevels.size(); i++){
            Level currentLevel = practiceLevels[i];
            //Sets up the Byte Arrays
            QByteArray levelNumber(to_string(i).c_str(), to_string(i).length());
            QByteArray levelTime(to_string(currentLevel.getBestTime()).c_str(), to_string(currentLevel.getBestTime()).length());
            QByteArray levelCompleted(BoolToString(currentLevel.isCompleted()).c_str(), BoolToString(currentLevel.isCompleted()).length());
            givenFile.write(QByteArray(indent + indent + "\"level\":" + levelNumber + " { \n"));
            givenFile.write(QByteArray(indent + indent + indent + "\"levelCompleted\":" + levelCompleted + ", \n"));
            givenFile.write(QByteArray(indent + indent + indent + "\"levelTime\":" + levelTime + "} \n"));
        }
        givenFile.write(QByteArray(indent + "} \n"));
        givenFile.write(QByteArray("} \n"));
        givenFile.flush();
        givenFile.close();
    }
}

/**
 * @brief Model::loadFile
 * loads the players data from a config text file
 */
void Model::loadFile(){
    fstream newfile;
    bool loadLevels = false;
    int curIndex = 0;
    int time = 0;
    newfile.open("config.txt",ios::in);  // open a file to perform write operation using file object
    if (newfile.is_open()) {
        string line;
        while (getline (newfile, line)) {
            if(line.find("levels") != std::string::npos){
                loadLevels = true;
            }
            else if(line.find("levelTime") != std::string::npos && loadLevels){
                time = stoi(line.substr(line.find(":") + 1, line.find("}")));
            }
            else if(line.find("levelCompleted") != std::string::npos && loadLevels){
                string curBool = line.substr(line.find(":") + 1, line.find(",")- line.find(":") -1);
                if(curBool == "false")
                    practiceLevels[curIndex].notCompleted();
                else
                    practiceLevels[curIndex].completed();
                practiceLevels[curIndex].inputTime(time);
            }
            else if(line.find("level") != std::string::npos && loadLevels){
                curIndex = stoi(line.substr(line.find(":") + 1, line.find("{")));
            }
            else if(line.find("}") != std::string::npos && loadLevels){
                loadLevels = false;
            }
        }
    }
    newfile.close();
}

/**
 * @brief Model::BoolToString
 * Helper method for converting a boolean to its string form. Used when
 * saving and loading the file.
 * @param givenBool
 * the input bool
 * @return
 * a string reading either true or false
 */
string Model::BoolToString(bool givenBool)
{
    return givenBool ? "true" : "false";
}

/**
 * @brief Model::recieveMatch
 * handles all the logic for when a correct or incorrect match is made
 * @param match
 * TRUE if match was correct, FALSE if match was incorrect.
 */
void Model::recieveMatch(bool match){

    if(match){
        matches++;
        if(matches==currentLevel->LevelSize){
            int time=timer.nsecsElapsed();
            currentLevel->inputTime(time);
            currentLevel->completed();
            saveFile();
            emit updateLevel();
        }
    }
    else{
        mistakes++;
    }
}

/**
 * @brief Model::sendLevelData
 * helper method for loading in the completion of levels from a saved file
 */
void Model::sendLevelData(){
    emit loadCompletion(practiceLevels);
}
