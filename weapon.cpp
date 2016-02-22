#include "weapon.h"

Weapon::Weapon()
{
    damage.cutting[CURRENT] = 0;
    damage.cutting[MAX] = 0;
    damage.shock[CURRENT] = 0;
    damage.shock[MAX] = 0;

    condition[CURRENT] = 0;
    condition[MAX] = 0;
    range = 0.0;
    is_range = false;
}

