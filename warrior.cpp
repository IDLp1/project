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
    move_order.x = -1;
    move_order.y = -1;
    is_move_order = false;
    current_step = 0;
    weapon = NULL;
    for(int i(0); i < MAX_STEPS; i++)
    {
        step[i].pos.x = 0;
        step[i].pos.y = 0;
        step[i].fordable = true;
    }
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

void Warrior::Calc()
{
    SetMaxHealth(endurance * 50 + strenght * 25 + 100);
    SetMaxStamina(endurance * 50 + 100);
    damage = 1.0 + strenght * 0.1;
    accuracy = agility * 50 + intellect * 25 + 100;
    dodge = agility * 50 + 100;
    crit_proc = sqrt((double)intellect / 2) * 5;
    SetMaxPointAction(level*2 + 30);
    SetPAPerMove(5 - agility / 5);
    SetPAPerAttack(10 - agility / 3);
}

void Warrior::Spawn(int _x, int _y, Fraction *_fraction, int _strenght, int _agility, int _intellect, int _endurance, int _level)
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
    strenght = _strenght;
    agility = _agility;
    intellect = _intellect;
    endurance = _endurance;
    level = _level;
    this->Calc();
    SetHealth(GetHealth(MAX));
    SetStamina(GetStamina(MAX));
    SetPointAction(GetPointAction(MAX));
}

void Warrior::SetMoveOrder(Vector2i _vector)
{
    move_order = _vector;
    is_move_order = true;
    /*Vector2i pointer;
    pointer.x = this->GetPosition().x;
    pointer.y = this->GetPosition().y;
    cout << "start p = " <<  pointer.x << ", " << pointer.y << endl;
    for(int i(0); i < MAX_STEPS; i++)
    {
        if(pointer.x - move_order.x < 0) step[i].x = 1;
        else if(pointer.x - move_order.x == 0) step[i].x = 0;
        else step[i].x = -1;
        if(pointer.y - move_order.y < 0) step[i].y = 1;
        else if(pointer.y - move_order.y == 0) step[i].y = 0;
        else step[i].y = -1;

        pointer.x += step[i].x;
        pointer.y += step[i].y;
        cout << "step[" << i << "] = " <<  step[i].x << ", " << step[i].y << endl;
        cout << "p = " <<  pointer.x << ", " << pointer.y << endl;
        if(step[i].x == 0 && step[i].y == 0) break;
    }
*/
}
void Warrior::ClearOrder()
{
    move_order.x = -1;
    move_order.y = -1;
    is_move_order = false;
    current_step = 0;
    for(int i(0); i < MAX_STEPS; i++)
    {
        step[i].pos = Vector2i(0, 0);
    }
}

bool Warrior::MoveOrder()
{
    if(is_move_order)
    {
        if(step[current_step].pos.x == 0 && step[current_step].pos.y == 0)
        {
            ClearOrder();
            return false;
        }
        else
        {
            if(this->Move(step[current_step].pos.x, step[current_step].pos.y))
            {
                current_step++;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

void Warrior::SetWeapon(Weapon *_weapon)
{
    if(_weapon->IsExist())
    {
        weapon = _weapon;
        _weapon->SetPosition(GetPosition());
    }
}

bool Warrior::Move(int _x, int _y)
{
    if(weapon != NULL) weapon->SetPosition(Vector2i(_x, _y));
    Unit::Move(_x, _y);
}

Vector2i Warrior::GetMoveOrder()
{
    return Vector2i(move_order.x, move_order.y);
}

float Warrior::GetDamage()
{
    return damage;
}

int Warrior::GetDodge()
{
    return dodge;
}

int Warrior::GetAccuracy()
{
    return accuracy;
}

float Warrior::GetCritProc()
{
    return crit_proc;
}

int Warrior::GetLevel()
{
    return level;
}


