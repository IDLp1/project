#ifndef DECORATION_H
#define DECORATION_H

#define MINE_NONE   0
#define MINE_WOOD   1
#define MINE_STONE  2
#define MINE_IRON   3

#define MAX_MINECELLS   4

#include "main.h"
#include "cell.h"
#include "camera.h"

class Mine
{
public:
    Mine(){};
    void    Set(int _id, int _amount);
    int     GetID();
private:
    int id;
    int amount;
};
class DecorationProt
{
public:
    DecorationProt();
    int         id;
    bool        is_active;
    char        name[64];
    Sprite      sprite;
    Texture     texture;
    double      transparency;
    double      fordable;
    int         size[2];
    bool        is_minning;
    Mine        mine[MAX_MINECELLS];
};

class Decoration
{
public:
    char    name[64];
    bool    is_active;
    Decoration();
    DecorationProt*     dec_prot;
    bool                is_minning;
    Mine                mine[MAX_MINECELLS];

    void                SetPosition(int _x, int _y);
    void                SetPosition(Vector2i vector);
    void                SetProt(DecorationProt* _dec_prot);

    Vector2f            GetRealPosition(Camera* camera);
private:
    Vector2i    position_map;
    Vector2f    position_real;
};

#endif // DECORATION_H
