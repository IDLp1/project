#ifndef CELL_H
#define CELL_H

#include "main.h"


#define CELL_SIZE   64

const double cd_cell_size = 64.0;
const int ci_cell_size = 64;
struct CellProt
{
    bool            is_active;
    int             rand_sprite; // количество рандомных спрайтов
    char            name[64];
    char            sprite_name[64];
    bool            edge;
    int             id;
    int             level;
    double          fordable;
    int             dismorale;
    Sprite          sprite;
};

class Cell
{
public:
    Cell();

    void    SetOfCellProt(CellProt* _cellprot);

    void    SetSprite(Sprite*);
    void    SetSprite(Sprite*, IntRect);
    void    SetIntRect(IntRect);
    void    SetFordable(double);
    void    SetDismorale(int);
    void    SetVisible(bool);

    void        SetPosition(int x, int y);
    Vector2f    GetRealPosition();
    Vector2i    GetMapPosition();
    double      GetFordable();
    int         GetDismorale();
    bool        GetVisible();

    Sprite*     sprite;
    CellProt*   cellprot;
    bool        is_active;
    int         rand_sprite;
private:

    Vector2i    position_map;
    Vector2f    position_real;
     // количество рандомных спрайтов
    double          fordable; //проходимость 1.0 = 100%
    int             dismorale;
    bool        visible;
};

Vector2f GetRealPosition(Vector2i _vector, bool center);

#endif // CELL_H
