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

void Warrior::MoveOrder()
{
    if(is_move_order)
    {
        if(step[current_step].pos.x == 0 && step[current_step].pos.y == 0)
        {
            ClearOrder();
        }
        else
        {
            this->Move(step[current_step].pos.x, step[current_step].pos.y);
            current_step++;
        }
    }
}

Vector2i Warrior::GetMoveOrder()
{
    return Vector2i(move_order.x, move_order.y);
}
