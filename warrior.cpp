#include "warrior.h"

Warrior::Warrior()
{
    fraction = NULL;
    strenght = 0;
    agility = 0;
    intellect = 0;
    endurance = 0;
    level = 0;
    accuracy = 0;
    dodge = 0;
    damage = 0;
    hungry = 0;
    morale = 0;
}

void Warrior::Spawn(int _x, int _y, Fraction* _fraction)
{
    is_alive = true;
    SetPosition(Vector2i(_x, _y));
    fraction = _fraction;
    if(fraction != NULL)
    {
        if(fraction->color != NULL)
        {
            sprite.setColor(*fraction->color);
        }
        else
        {
            cout << "Warning: fraction has no color";
        }
    }
    else
    {
        cout << "Warning: warrior has no faction" << endl;
    }
}
