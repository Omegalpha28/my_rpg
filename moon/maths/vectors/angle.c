/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** angle
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
float angle2f(v2f_t a, v2f_t b)
{
    float dot = dot2f(a, b);
    float mag = sqrtf(dot2f(a, a) * dot2f(b, b));

    return (acosf(dot / mag));
}

///////////////////////////////////////////////////////////////////////////////
float angle2i(v2i_t a, v2i_t b)
{
    v2f_t af = (v2f_t){(float)a.x, (float)a.y};
    v2f_t bf = (v2f_t){(float)b.x, (float)b.y};
    float dot = dot2f(af, bf);
    float mag = sqrtf(dot2f(af, af) * dot2f(bf, bf));

    return (acosf(dot / mag));
}

///////////////////////////////////////////////////////////////////////////////
float angle2u(v2u_t a, v2u_t b)
{
    v2f_t af = (v2f_t){(float)a.x, (float)a.y};
    v2f_t bf = (v2f_t){(float)b.x, (float)b.y};
    float dot = dot2f(af, bf);
    float mag = sqrtf(dot2f(af, af) * dot2f(bf, bf));

    return (acosf(dot / mag));
}

///////////////////////////////////////////////////////////////////////////////
float angle3f(v3f_t a, v3f_t b)
{
    float dot = dot3f(a, b);
    float mag = sqrtf(dot3f(a, a) * dot3f(b, b));

    return (acosf(dot / mag));
}
