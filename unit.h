#ifndef UNIT_H
#define UNIT_H

#include "main.h"
#include "camera.h"
#include "cell.h"

class Unit
{
public:
    Unit();
    bool    is_selected;
    bool    is_alive;
    //Texture    texture;
    Sprite     sprite;

    void    SetHealth(int _health, int _max);
    void    SetDamage(int _damage, int type);
    void    SetStamina(int _stamina, int _max);
    void    SetPointAction(int _point_action, int _max);
    void    SetPosition(int _x, int _y);
    void    SetPosition(Vector2i vector);
    void    SetRealPosition(); //Нужны данные с камеры
    void    Move(int _x, int _y);
    //
    int     GetHealth(int _max);

    int         GetStamina(int _max);
    int         GetPointAction(int _max);
    Vector2i    GetPosition();
    Vector2f    GetRealPosition(Camera* camera);

private:
    int     health[2];
    int     stamina[2];
    int     point_action[2];




    Vector2i    position_map;
};

#endif // UNIT_H
