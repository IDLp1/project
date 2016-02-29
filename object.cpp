#include "object.h"

Object::Object()
{
    position = Vector2i(-1, -1);
    is_exist = false;
    in_possesion = false;
}

Vector2i    Object::GetPosition()
{
    return Vector2i(position.x, position.y);
}

Vector2f    Object::GetRealPosition()
{
    return Vector2f(position.x * cd_cell_size + cd_cell_size / 2.0, position.y * cd_cell_size + cd_cell_size / 2.0);
}

void Object::SetPosition(Vector2i _vector)
{
    position.x = _vector.x;
    position.y = _vector.y;
}

bool        Object::IsExist()
{
    return is_exist;
}

bool        Object::In_possesion()
{
    return in_possesion;
}

void Object::Spawn(Vector2i _pos)
{
    SetPosition(_pos);
    is_exist = true;
}


void Object::Destroy()
{
    is_exist = false;
    in_possesion = false;
    position = Vector2i(-1, -1);
}
