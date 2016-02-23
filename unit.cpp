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

void Unit::SetHealth(int _health)
{
    health[CURRENT] = _health;
}

void Unit::SetStamina(int _stamina)
{
    stamina[CURRENT] = _stamina;
}
void Unit::SetPointAction(int _point_action)
{
    point_action[CURRENT] = _point_action;
}
void Unit::SetMaxHealth(int _health)
{
    health[MAX] = _health;
}

void Unit::SetMaxStamina(int _stamina)
{
    stamina[MAX] = _stamina;
}
void Unit::SetMaxPointAction(int _point_action)
{
    point_action[MAX] = _point_action;
}

void Unit::SetDamage(int _damage, int type)
{

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

void Unit::SetPAPerAttack(int _set)
{
    pa_per_attack = _set;
}

void Unit::SetPAPerMove(int _set)
{
    pa_per_move = _set;
}

int Unit::GetHealth(int _max)
{
    return health[_max];
}

int Unit::GetStamina(int _max)
{
    return stamina[_max];
}

bool Unit::Move(int _x, int _y)
{
    if((point_action[CURRENT] - pa_per_move) >= 0)
    {
        position_map.x += _x;
        position_map.y += _y;
        point_action[CURRENT] -= pa_per_move;
        return true;
    }
    else
    {
        return false;
    }
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



