#ifndef WARRIOR_H
#define WARRIOR_H

#define MAX_STEPS   64
#define MAX_WARRIOR         64

#include "main.h"
#include "unit.h"
#include "fraction.h"
#include "weapon.h"

const float cf_size_warrior = 64.0;

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
    void Spawn(int _x, int _y, Fraction *_fraction, int _strenght, int _agility, int _intellect, int _endurance, int _level);
    void Calc();
    void SetMoveOrder(Vector2i _vector);
    bool MoveOrder();
    void ClearOrder();
    void SetWeapon(Weapon* _weapon);
    bool Move(int _x, int _y);
    bool    is_move_order;
    Step    step[MAX_STEPS];
    int     current_step;

    Vector2i    GetMoveOrder();
    float       GetDamage();
    int         GetDodge();
    int         GetAccuracy();
    float       GetCritProc();
    int         GetLevel();
    Weapon* weapon;
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
    float   crit_proc; //процент крита

    //расходы


    //состояние

    int hungry;
    int morale;

};

#endif // WARRIOR_H
