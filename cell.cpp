#include "cell.h"

Cell::Cell()
{
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
    return position_real;
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

Map::Map()
{
    for(int i; i < MAX_CELLS; i++)
    {
        cell[i] = 0;
    }
    size_w = 0;
    size_h = 0;
}

void Map::SetSize(unsigned int _size_w, unsigned int _size_h)
{
    size_w = _size_w;
    size_h = _size_h;
}

void Map::GenerateRandom(int _min_id, int _max_id)
{
    unsigned int size = size_w * size_h;
    if(size > MAX_CELLS)
    {
        cout << "Error: Size map > MAX_CEELS";
    }
    else
    {
        for(int i(0); i < size; i++)
        {
            cell[i] = random(_min_id, _max_id);
        }
    }
}

void Map::OutInConsole()
{
    unsigned int size = size_w * size_h;
    cout << "Map size_w = " << size_w << " size_h = " << size_h << " all size = " << size <<endl;
    for(int i(0); i < size; i++)
    {
        cout << i << "=" << cell[i] << " ";
    }
    cout << endl;
}

int Map::GetMaxSize()
{
    return size_h * size_w;
}

int Map::GetSizeW()
{
    return size_w;
}

int Map::GetSizeH()
{
    return size_h;
}
