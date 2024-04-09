/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** distance
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
int distance2i(v2i pts1, v2i pts2)
{
    int dx = pts2.x - pts1.x;
    int dy = pts2.y - pts1.y;

    return ((int)sqrtf((dx * dx) + (dy * dy)));
}

///////////////////////////////////////////////////////////////////////////////
float distance2f(v2f pts1, v2f pts2)
{
    float dx = pts2.x - pts1.x;
    float dy = pts2.y - pts1.y;

    return (sqrtf((dx * dx) + (dy * dy)));
}

///////////////////////////////////////////////////////////////////////////////
int distance2u(v2u pts1, v2u pts2)
{
    int dx = pts2.x - pts1.x;
    int dy = pts2.y - pts1.y;

    return ((int)sqrtf((dx * dx) + (dy * dy)));
}

///////////////////////////////////////////////////////////////////////////////
float distance3f(v3f pts1, v3f pts2)
{
    float dx = pts2.x - pts1.x;
    float dy = pts2.y - pts1.y;
    float dz = pts2.y - pts1.y;

    return (sqrtf((dx * dx) + (dy * dy) + (dz * dz)));
}
