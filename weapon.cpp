#include "weapon.h"

Damage::Damage()
{
    cutting[MIN] = 0;
    cutting[MAX] = 0;
    shock[MIN] = 0;
    shock[MAX] = 0;
}


Damage::Damage(int _min_cutting, int _max_cutting, int _min_shock, int _max_shock)
{
    cutting[MIN] = _min_cutting;
    cutting[MAX] = _max_cutting;
    shock[MIN] = _min_shock;
    shock[MAX] = _max_shock;
}
WeaponProt::WeaponProt()
{
    strclear(name);
    condition = 0;
    range = 0.0f;
    is_range = false;
}
void Damage::operator=(Damage _damage)
{
    cutting[MIN] = _damage.cutting[MIN];
    cutting[MAX] = _damage.cutting[MAX];
    shock[MIN] = _damage.shock[MIN];
    shock[MAX] = _damage.shock[MAX];
}

Damage Damage::operator-(Damage _damage)
{
    return Damage(cutting[MIN] - _damage.cutting[MIN],
                  cutting[MAX] - _damage.cutting[MAX],
                  shock[MIN] - _damage.shock[MIN],
                  shock[MAX] - _damage.shock[MAX]);
}
Damage Damage::operator+(Damage _damage)
{
    return Damage(cutting[MIN] + _damage.cutting[MIN],
                  cutting[MAX] + _damage.cutting[MAX],
                  shock[MIN] + _damage.shock[MIN],
                  shock[MAX] + _damage.shock[MAX]);
}

void WeaponProt::Set(char* _name, Damage _damage, int _condition, bool _is_range, float _range)
{
    strcpy(name, _name);
    damage = _damage;
    condition = _condition;
    is_range = _is_range;
    range = _range;
}

Weapon::Weapon()
{
    condition[CURRENT] = 0;
    condition[MAX] = 0;
    range = 0.0f;
    damage = Damage(0, 0, 0, 0);
    is_range = false;
}

void Weapon::Spawn(Vector2i _pos, WeaponProt *_wp)
{
    Object::Spawn(_pos);
    this->Set(_wp);
}

void Weapon::Set(WeaponProt *_wp)
{
    weapon_prot = _wp;
    damage = _wp->damage;
    condition[MAX] = _wp->condition;
    is_range = _wp->is_range;
    range = _wp->range;
}
