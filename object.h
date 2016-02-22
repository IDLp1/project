#ifndef OBJECT_H
#define OBJECT_H

#include "main.h"
#include "cell.h"

class Object
{
public:
    Object();
    Vector2i    GetPosition();
    Vector2f    GetRealPosition();
    bool        IsExist();
    bool        In_possesion();
private:
    Vector2i position;
    bool    is_exist;
    bool    in_possesion;
};

#endif // OBJECT_H
