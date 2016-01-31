#ifndef MAP
#define MAP

#include "main.h"

class Map
{
public:
    Map();
    void GenerateRandom(int _min_id, int _max_id);
    void SetSize(unsigned int _size_w, unsigned int _size_h);
    void OutInConsole();
    int GetMaxSize();
    int GetSizeW();
    int GetSizeH();
    Vector2i    GetPosition(int _i);

    unsigned int    cell[MAX_CELLS];
    unsigned int    decoration[MAX_DECORATION];

private:
    unsigned int    size_w;
    unsigned int    size_h;

};

#endif // MAP

