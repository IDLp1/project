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

/*void Map::GenerateRandom(int _min_id, int _max_id)
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
}*/

void Map::GenerateRandom(unsigned int _size_w, unsigned int _size_h, unsigned int freq_dirt, unsigned int freq_stone)
{
    unsigned int size = _size_w * _size_h;
    if(size > MAX_CELLS)
    {
        cout << "Error: Size map > MAX_CEELS";
    }
    else
    {
        size_w = _size_w;
        size_h = _size_h;
        for(int i(0); i < size; i++) //заливка травой
        {
            cell[i] = CELL_ID_GREEN;
        }
        //создание грязевых массивов
        {
            Vector2i core;
            int freq = random(freq_dirt / 2, freq_dirt);
            for(int i(0); i < freq; i++)
            {
                core = Vector2i(random(0u, size_w), random(0u, size_h));
                cell[GetIdPosition(core)] = CELL_ID_DIRT;
                for(int j(0); j < freq;)
                {
                    core += Vector2i(random(-1, 1), random(-1, 1));
                    if(core.x < 0) core.x = 0;
                    else if(core.x > size_w) core.x = size_w;
                    else if(core.y < 0) core.y = 0;
                    else if(core.y > size_h) core.y = size_h;
                    else
                    {
                        cell[GetIdPosition(core)] = CELL_ID_DIRT;
                        j++;
                    }
                }
            }
        }
        //создание каменых массивов
        {
            Vector2i core;
            int freq = random(freq_stone / 2, freq_stone);
            for(int i(0); i < freq; i++)
            {
                core = Vector2i(random(0u, size_w), random(0u, size_h));
                cell[GetIdPosition(core)] = CELL_ID_DIRT;
                for(int j(0); j < freq;)
                {
                    core += Vector2i(random(-1, 1), random(-1, 1));
                    if(core.x < 0) core.x = 0;
                    else if(core.x > size_w) core.x = size_w;
                    else if(core.y < 0) core.y = 0;
                    else if(core.y > size_h) core.y = size_h;
                    else
                    {
                        cell[GetIdPosition(core)] = CELL_ID_STONE;
                        if(random(0, 100) > 90) decoration[GetIdPosition(core)] = 1;
                        j++;
                    }
                }
            }
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

int Map::GetIdPosition(Vector2i _vector)
{
    int id;
    id = _vector.y * size_w + _vector.x;
    return id;
}
