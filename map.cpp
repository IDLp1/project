#include "map.h"

Map::Map()
{
    for(int i; i < MAX_CELLS; i++)
    {
        cell[i] = 0;
    }
    for(int i; i < MAX_DECORATION; i++)
    {
        decoration[i] = 0;
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

Vector2i Map::GetPosition(int _i)
{
    Vector2i result;
    result.y = _i / size_w;
    result.x = _i % size_w;
    return result;
}
