#ifndef UNIT_H
#define UNIT_H

#include "main.h"

#include "cell.h"

class Unit
{
public:
    Unit();
    bool    is_selected;
    bool    is_alive;
    //Texture    texture;
    Sprite     sprite;

    void    SetHealth(int _health);
    void    SetMaxHealth(int _health);
    void    SetDamage(int _damage, int type);
    void    SetStamina(int _stamina);
    void    SetMaxStamina(int _stamina);
    void    SetPointAction(int _point_action);
    void    SetMaxPointAction(int _point_action);
    void    SetPosition(int _x, int _y);
    void    SetPosition(Vector2i vector);
    void    SetRealPosition(); //Нужны данные с камеры
    bool    Move(int _x, int _y);
    void         SetPAPerMove(int _set);
    void         SetPAPerAttack(int _set);
    //
    int     GetHealth(int _max);

    int         GetStamina(int _max);
    int         GetPointAction(int _max);
    Vector2i    GetPosition();
    Vector2f    GetRealPosition();
    int         GetPAPerMove();
    int         GetPAPerAttack();

private:
    int     health[2];
    int     stamina[2];
    int     point_action[2];

    int pa_per_move; // очков на ход
    int pa_per_attack; //очков на атаку



    Vector2i    position_map;
};

#endif // UNIT_H
