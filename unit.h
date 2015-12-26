#ifndef UNIT_H
#define UNIT_H

#include "main.h"

class Unit
{
public:
    Unit();
private:
    //Игровые динамичные
    Vector2i    position;
    int points_action[2];
    int health[2];
    int stamina[2];
    int morality;
    int fear;
    int dodge;
    int accuracy;
    int penalty_passability;

    //Игровые статичные

    int streinght;
    int agility;
    int intellect;
    int level;
    int bravery;


};

#endif // UNIT_H
