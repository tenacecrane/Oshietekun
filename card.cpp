#include "card.h"

card::card(string givenCardValue)
{
    cardValue = givenCardValue;
}

string card::getCardValue(){
    return cardValue;
}

void card::playCardSound(){
    //Play card sound
}
