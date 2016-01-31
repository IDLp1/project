#include "camera.h"

Camera::Camera()
{
    position.x = 0.0;
    position.y = 0.0;
}

void Camera::SetPosition(Vector2f _vector)
{
    position = _vector;
}

void Camera::Move(float _x, float _y)
{
    position.x += _x;
    position.y += _y;
    if(position.x < 0.0) position.x = 0.0;
    if(position.y < 0.0) position.y = 0.0;
}

Vector2f Camera::GetPosition()
{
    return Vector2f(position.x, position.y);
}
