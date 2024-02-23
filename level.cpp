/**
 * @file
 * @author Michael Sizemore, Kevin Macknight, Jack Gill, Tyson Fox, Ashton Foulger, Tenace Crane, Jacob Pelegrin, Mason Januszewski
 * @brief A8: An Educational App
 * @version 1.0
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 */
#include "level.h"

/**
 * @brief Level::Level A representation of one of the levels in the game
 */
Level::Level()
{
    levelCompleted = false;
    bestTime = -1;// should be set to 3min, high value for now
}

/**
 * @brief Level::isCompleted - gets the current value of the level to see if its completed
 * @return - gets the current value of the level to see if its completed
 */
bool Level::isCompleted(){
    return levelCompleted;
}

/**
 * @brief Level::getBestTime - Gets the int that is currently set as the best time
 * @return - Returns what is currently set as the best time
 */
int Level::getBestTime(){
    return bestTime;
}

/**
 * @brief Level::completed - sets the current level as completed
 */
void Level::completed(){
    levelCompleted = true;
}

/**
 * @brief Level::notCompleted - sets the current level so that its not completed.
 */
void Level::notCompleted(){
    levelCompleted = false;
}

/**
 * @brief Level::inputTime - Takes a given time after a level is completed. If the
 *  time that is given is better than the current best time than it will be updated.
 * @param givenTime - the given time that might be updated.
 */
void Level::inputTime(int givenTime){
    if(givenTime < bestTime||bestTime==-1)
        bestTime = givenTime;
}
