/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** endpoint
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
v2f_t endpoint2f(v2f_t origin, v2f_t direction, float distance)
{
    v2f_t normalized = subtract2f(direction, origin);
    float length = sqrtf(SQUARE(normalized.x) + SQUARE(normalized.y));

    normalized = divide2f(normalized, (v2f_t){length, length});
    return ((v2f_t){
        origin.x + normalized.x * distance,
        origin.y + normalized.y * distance
    });
}

///////////////////////////////////////////////////////////////////////////////
v2u_t endpoint2u(v2u_t origin, v2u_t direction, float distance)
{
    v2u_t normalized = subtract2u(direction, origin);
    float length = sqrtf((float)(SQUARE(normalized.x) + SQUARE(normalized.y)));

    normalized = divide2u(normalized, (v2u_t){length, length});
    return ((v2u_t){
        origin.x + (uint_t)(normalized.x * distance),
        origin.y + (uint_t)(normalized.y * distance)
    });
}

///////////////////////////////////////////////////////////////////////////////
v3f_t endpoint3f(v3f_t origin, v3f_t direction, float distance)
{
    v3f_t normalized = subtract3f(direction, origin);
    float length = sqrtf((float)(SQUARE(normalized.x) + SQUARE(normalized.y)
        + SQUARE(normalized.z)));

    normalized = divide3f(normalized, (v3f_t){length, length, length});
    return ((v3f_t){
        origin.x + (float)(normalized.x * distance),
        origin.y + (float)(normalized.y * distance),
        origin.z + (float)(normalized.z * distance)
    });
}

///////////////////////////////////////////////////////////////////////////////
v2i_t endpoint2i(v2i_t origin, v2i_t direction, float distance)
{
    v2i_t normalized = subtract2i(direction, origin);
    float length = sqrtf((float)(SQUARE(normalized.x) + SQUARE(normalized.y)));

    normalized = divide2i(normalized, (v2i_t){(int)(length), (int)(length)});
    return ((v2i_t){
        origin.x + (int)(normalized.x * distance),
        origin.y + (int)(normalized.y * distance)
    });
}
