/*
** EPITECH PROJECT, 2024
** my_rpg
** File description:
** movetowards
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
v2f_t movetowards2f(v2f_t current, v2f_t target, float maxDistanceDelta)
{
    v2f_t direction = {target.x - current.x, target.y - current.y};
    float distance = sqrtf(direction.x * direction.x +
        direction.y * direction.y);

    if (distance <= maxDistanceDelta || distance == 0)
        current = target;
    else {
        direction = divide2f(direction, (v2f_t){distance, distance});
        direction = multiply2f(direction,
            (v2f_t){maxDistanceDelta, maxDistanceDelta});
        current = add2f(current, direction);
    }
    return (current);
}

///////////////////////////////////////////////////////////////////////////////
v2u_t movetowards2u(v2u_t current, v2u_t target, float maxDistanceDelta)
{
    v2u_t direction = {target.x - current.x, target.y - current.y};
    float distance = sqrtf(direction.x * direction.x +
        direction.y * direction.y);

    if (distance <= maxDistanceDelta || distance == 0)
        current = target;
    else {
        direction = divide2u(direction, (v2u_t){distance, distance});
        direction = multiply2u(direction,
            (v2u_t){maxDistanceDelta, maxDistanceDelta});
        current = add2u(current, direction);
    }
    return (current);
}

///////////////////////////////////////////////////////////////////////////////
v2i_t movetowards2i(v2i_t current, v2i_t target, float maxDistanceDelta)
{
    v2i_t direction = {target.x - current.x, target.y - current.y};
    float distance = sqrtf(direction.x * direction.x +
        direction.y * direction.y);

    if (distance <= maxDistanceDelta || distance == 0)
        current = target;
    else {
        direction = divide2i(direction, (v2i_t){distance, distance});
        direction = multiply2i(direction,
            (v2i_t){maxDistanceDelta, maxDistanceDelta});
        current = add2i(current, direction);
    }
    return (current);
}
