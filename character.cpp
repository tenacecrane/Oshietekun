/**
 * @file
 * @author Michael Sizemore, Kevin Macknight, Jack Gill, Tyson Fox, Ashton Foulger, Tenace Crane, Jacob Pelegrin, Mason Januszewski
 * @brief A8: An Educational App
 * @version 1.0
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 */
#include "character.h"

/**
 * @brief Character::Character - This class represents a single japanese character
 * and its different representations in romaki, hiragana, and katakana.
 */
Character::Character(){
    romajiValue = "";
    hiraganaValue = "";
    katakanaValue = "";
}

/**
 * @brief Character::Character - This class represents a single japanese character
 * and its different representations in romaki, hiragana, and katakana. This constructor
 * takes in each of these representations and assigns them correctly.
 *
 * @param p - the characters position in the vector
 * @param givenRomaji - the given Romanji value
 * @param givenHiragana - the given Hirigana vale
 * @param givenKatakana - the given Katakana value
 */
Character::Character(int p, string givenRomaji, string givenHiragana, string givenKatakana)
{
    position=p;
    romajiValue = givenRomaji;
    hiraganaValue = givenHiragana;
    katakanaValue = givenKatakana;
}

/**
 * @brief Character::getRomaji - Returns the romaji value tied to the character
 * @return Returns the romaji value tied to the character
 */
string Character::getRomaji()const{
    return romajiValue;
}

/**
 * @brief Character::getHirigana - Returns the Hirigana value tied to the character
 * @return Returns the Hirigana value tied to the character
 */
string Character::getHiragana()const{
    return hiraganaValue;
}

/**
 * @brief Character::getKatakana - Returns the Katakana value tied to the character
 * @return Returns the Katakana value tied to the character
 */
string Character::getKatakana()const{
    return katakanaValue;
}

/**
 * @brief Character::getPosition - Returns the characters position in the character vector
 * @return Returns the characters position in the character vector
 */
int Character::getPosition()const{
    return position;
}
