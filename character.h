/**
 * @file
 * @author Michael Sizemore, Kevin Macknight, Jack Gill, Tyson Fox, Ashton Foulger, Tenace Crane, Jacob Pelegrin, Mason Januszewski
 * @brief A8: An Educational App
 * @version 1.0
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include "vector"
#include "QUrl"

using namespace std;

class Character
{
public:
    Character();
    Character(int position, string givenRomaji, string givenHiragana, string givenKatakana);
     string getRomaji()const;
     string getHiragana()const;
     string getKatakana()const;
     int getPosition()const;

private:
     string romajiValue;
     string hiraganaValue;
     string katakanaValue;
     int position;
};

#endif // CHARACTER_H
