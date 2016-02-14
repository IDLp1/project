#include "unit.h"

Unit::Unit()
{
    is_selected = false;
    is_alive = false;
    health[CURRENT] = 0;
    health[MAX] = 0;
    stamina[CURRENT]= 0;
    stamina[MAX]= 0;
    point_action[CURRENT] = 0;
    point_action[MAX] = 0;
    position_map.x = 0;
    position_map.y = 0;
    /*position_real.x = 0.0;
    position_real.y = 0.0;*/
}

void Unit::SetHealth(int _health, int _max)
{
    health[_max] = _health;
}

void Unit::SetDamage(int _damage, int type)
{

}
void Unit::SetStamina(int _stamina, int _max)
{
    stamina[_max] = _stamina;
}
void Unit::SetPointAction(int _point_action, int _max)
{
    point_action[_max] = _point_action;
}
void Unit::SetPosition(int _x, int _y)
{
    position_map.x = _x;
    position_map.y = _y;
}
void Unit::SetPosition(Vector2i vector)
{
    position_map.x = vector.x;
    position_map.y = vector.y;
}

int Unit::GetHealth(int _max)
{
    return health[_max];
}

int Unit::GetStamina(int _max)
{
    return stamina[_max];
}

void Unit::Move(int _x, int _y)
{
    position_map.x += _x;
    position_map.y += _y;
}

int Unit::GetPointAction(int _max)
{
    return point_action[_max];
}

Vector2i Unit::GetPosition()
{
    return Vector2i(position_map.x, position_map.y);
}

Vector2f Unit::GetRealPosition() // при setOrigin в центре
{
    return Vector2f(position_map.x * cd_cell_size + cd_cell_size / 2.0, position_map.y * cd_cell_size + cd_cell_size / 2.0);
}
