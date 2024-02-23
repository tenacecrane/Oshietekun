/**
 * @file
 * @author Michael Sizemore, Kevin Macknight, Jack Gill, Tyson Fox, Ashton Foulger, Tenace Crane, Jacob Pelegrin, Mason Januszewski
 * @brief A8: An Educational App
 * @version 1.0
 * @date 2022-04-25
 *
 * @copyright Copyright (c) 2022
 */
#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "QVector"
#include "character.h"

using namespace std;

class Level
{
public:
    Level();
    bool isCompleted();
    int getBestTime();
    void completed();
    void notCompleted();
    void inputTime(int givenTime);
    int LevelSize;

private:
    bool levelCompleted;
    int bestTime;
};

#endif // LEVEL_H
