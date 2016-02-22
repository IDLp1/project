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

bool        Object::IsExist()
{

}

bool        Object::In_possesion()
{

}
