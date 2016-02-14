#include "cell.h"

Cell::Cell()
{
    position_map.x = 0;
    position_map.y = 0;
    position_real.x = 0.0;
    position_real.y = 0.0;

    sprite = NULL;
    cellprot = NULL;
    rand_sprite = 0;

    fordable = 0.0;
    dismorale = 0;
    visible = false;
    is_active = false;
}

void Cell::SetOfCellProt(CellProt *_cellprot)
{
    sprite = &_cellprot->sprite;
    rand_sprite = random(0, _cellprot->rand_sprite - 1);
    cellprot = _cellprot;
    fordable = _cellprot->fordable;
    dismorale = _cellprot->dismorale;
}

void Cell::SetSprite(Sprite* _sprite)
{

}

void Cell::SetSprite(Sprite* _sprite, IntRect _int_rect)
{

}

void Cell::SetIntRect(IntRect _int_rect)
{

}

void Cell::SetFordable(double _fordable)
{

}


void Cell::SetDismorale(int _dismorale)
{

}

void Cell::SetVisible(bool _visible)
{

}
void Cell::SetPosition(int _x, int _y)
{
    position_map.x = _x;
    position_map.y = _y;
    position_real.x = (double)(_x * cd_cell_size);
    position_real.y = (double)(_y * cd_cell_size);
}

Vector2i Cell::GetMapPosition()
{
    return position_map;
}

Vector2f Cell::GetRealPosition()
{
    return Vector2f(position_real.x, position_real.y);
}

double Cell::GetFordable()
{

}


int Cell::GetDismorale()
{

}

bool Cell::GetVisible()
{

}

Vector2f GetRealPosition(Vector2i _vector, bool center)
{
    if(!center) return Vector2f((float)_vector.x * cd_cell_size, (float)_vector.y * cd_cell_size);
    else return Vector2f((float)_vector.x * cd_cell_size + cd_cell_size / 2.0, (float)_vector.y * cd_cell_size + cd_cell_size / 2.0);
}
