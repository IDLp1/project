#include "decoration.h"

void Mine::Set(int _id, int _amount)
{
    id = _id;
    amount = _amount;
}

int Mine::GetID()
{
    return id;
}

DecorationProt::DecorationProt()
{
    id = 0;
    is_active = false;
    strclear(name);
    transparency = 0.0;
    fordable = 0.0;
    size[_W] = 0;
    size[_H] = 0;
    is_minning = false;
    for(int i = 0; i < MAX_MINECELLS; i++)
    {
        mine[i].Set(0, 0);
    }
}

Decoration::Decoration()
{
    strclear(name);
    is_active = false;
    dec_prot = NULL;
    position_map.x = 0;
    position_map.y = 0;
    position_real.x = 0.0;
    position_real.y = 0.0;
    is_minning = false;
    for(int i = 0; i < MAX_MINECELLS; i++)
    {
        mine[i].Set(0, 0);
    }
}

void Decoration::SetProt(DecorationProt *_dec_prot)
{
    dec_prot = _dec_prot;
}

void Decoration::SetPosition(int _x, int _y)
{

}
void Decoration::SetPosition(Vector2i vector)
{
    position_map = vector;
    position_real.x = vector.x * cd_cell_size;
    position_real.y = vector.y * cd_cell_size;
}

Vector2f Decoration::GetRealPosition()
{
    return Vector2f(position_real.x, position_real.y);
}

Vector2i Decoration::GetPosition()
{
    return Vector2i(position_map.x, position_map.y);
}
