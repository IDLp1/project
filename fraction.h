#ifndef FRACTION_H
#define FRACTION_H
#include "main.h"

const int c_color_red_fraction[] = {255, 0, 0};
const int c_color_blue_fraction[] = {0, 0, 255};
const int c_color_green_fraction[] = {0, 255, 0};
const int c_color_yellow_fraction[] = {255, 253, 0};

class Fraction
{

public:
    Fraction();
    void    SetGold(int _gold);
    void    SetColor(Color* _color);

    int    GetGold();

    Color* color;
    bool    is_game;
    bool    is_move;
private:

    int gold;
};

#endif // FRACTION_H
