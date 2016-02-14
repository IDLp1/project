#ifndef WARRIOR_H
#define WARRIOR_H

#define MAX_STEPS   64

#include "main.h"
#include "unit.h"
#include "fraction.h"

const float cf_size_warrior = 48.0;

struct Step
{
    Vector2i pos;
    bool    fordable;
};

class Warrior : public Unit
{

public:
    Warrior();
    void Spawn(int _x, int _y, Fraction* _fraction); //простой спавн, далее нужна будет перегрузка под более серьезные спавны, возможно даже скриптами
    void SetMoveOrder(Vector2i _vector);
    void MoveOrder();
    void ClearOrder();
    bool    is_move_order;
    Step    step[MAX_STEPS];
    int     current_step;
    Vector2i GetMoveOrder();
private:

    //игровые данные

    Fraction* fraction;
    Vector2i move_order;

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
