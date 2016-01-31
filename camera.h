#ifndef CAMERA_H
#define CAMERA_H
#include "main.h"

const float cf_camera_speed = 4.0;

class Camera
{
public:
    Camera();
    void        SetPosition(Vector2f _vector);
    void        Move(float _x, float _y);
    Vector2f    GetPosition();
private:
    Vector2f    position;
};

#endif // CAMERA_H
