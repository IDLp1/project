#ifndef WARRIOR_H
#define WARRIOR_H
#include "main.h"
#include "unit.h"
#include "fraction.h"

class Warrior : public Unit
{

public:
    Warrior();
    void Spawn(int _x, int _y, Fraction* _fraction); //простой спавн, далее нужна будет перегрузка под более серьезные спавны, возможно даже скриптами

private:

    //игровые данные

    Fraction* fraction;

    //физические статы
    int strenght;
    int agility;
    int intellect;
    int endurance; //выносливость
    int level;

    //боевые статы
    int accuracy;
    int dodge;
    float   damage;
    //состояние

    int hungry;
    int morale;

};

#endif // WARRIOR_H
