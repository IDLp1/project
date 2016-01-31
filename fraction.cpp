#include "fraction.h"

Fraction::Fraction()
{
    color = NULL;
    gold = 0;
    is_move = false;
    is_game = false;
}


void Fraction::SetGold(int _gold)
{
    gold = _gold;
}

void Fraction::SetColor(Color* _color)
{
    color = _color;
}

int Fraction::GetGold()
{
    return gold;
}
