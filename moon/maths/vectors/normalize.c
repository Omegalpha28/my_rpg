/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** normalize
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
v2f_t normalize2f(v2f_t vec)
{
    float mag = sqrtf((float)(SQUARE(vec.x) + SQUARE(vec.y)));

    if (mag > 0.0f) {
        vec.x /= mag;
        vec.y /= mag;
    }
    return (vec);
}

///////////////////////////////////////////////////////////////////////////////
v2i_t normalize2i(v2i_t vec)
{
    float mag = sqrtf((float)(SQUARE(vec.x) + SQUARE(vec.y)));

    if (mag > 0.0f) {
        vec.x /= mag;
        vec.y /= mag;
    }
    return (vec);
}

///////////////////////////////////////////////////////////////////////////////
v2u_t normalize2u(v2u_t vec)
{
    float mag = sqrtf((float)(SQUARE(vec.x) + SQUARE(vec.y)));

    if (mag > 0.0f) {
        vec.x /= mag;
        vec.y /= mag;
    }
    return (vec);
}

///////////////////////////////////////////////////////////////////////////////
v3f_t normalize3f(v3f_t vec)
{
    float mag = sqrtf((float)(SQUARE(vec.x) + SQUARE(vec.y) + SQUARE(vec.z)));

    if (mag > 0.0f) {
        vec.x /= mag;
        vec.y /= mag;
        vec.z /= mag;
    }
    return (vec);
}
