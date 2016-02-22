#ifndef WEAPON_H
#define WEAPON_H

#include "main.h"
#include "object.h"
#include "warrior.h"

struct Damage
{
    int cutting[2];
    int shock[2];
};

class WeaponProt
{
public:
    Sprite* sprite;
    Damage  damage;
    int     condition;

};

class Weapon : public Object
{
public:
    Weapon();
    WeaponProt* weapon_prot;
private:
    Damage      damage;
    int         condition[2];
    bool        is_range;
    double      range;
};

#endif // WEAPON_H
