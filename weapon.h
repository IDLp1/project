#ifndef WEAPON_H
#define WEAPON_H

#include "main.h"
#include "object.h"

#define MAX_WEAPONS         128
#define MAX_WEAPONS_PROT    16
#define WPP_SWORD   0

class Damage
{
public:
    Damage();
    Damage(int _min_cutting, int _max_cutting, int _min_shock, int _max_shock);
    int cutting[2];
    int shock[2];
    void operator=(Damage _damage);
    Damage operator-(Damage _damage);
    Damage operator+(Damage _damage);
};

class WeaponProt
{
public:
    WeaponProt();
    void    Set(char* _name, Damage _damage, int _condition, bool _is_range, float _range);
    char    name[64];
    Sprite  sprite;
    Damage  damage;
    int     condition;
    bool    is_range;
    float  range;
};

class Weapon : public Object
{
public:
    Weapon();
    WeaponProt* weapon_prot;
    void    Set(WeaponProt* _wp);
    void    Spawn(Vector2i _pos, WeaponProt* _wp);
private:
    Damage      damage;
    int         condition[2];
    bool        is_range;
    float      range;
};

#endif // WEAPON_H
