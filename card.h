#ifndef CARD_H
#define CARD_H

#include <iostream>

using namespace std;

class card
{
public:
    card(string givenCardValue);
    string getCardValue();
    void playCardSound();//Return sound if can not be played in this method
private:
    string cardValue;
    string cardSound;//Needs to be set to QSound or sound object
};

#endif // CARD_H
