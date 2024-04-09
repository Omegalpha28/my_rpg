/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** min
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
int min(uint n, int x, ...)
{
    int minimum = x;
    int arg;
    va_list args;

    va_start(args, x);
    for (uint i = 0; i < (n - 1); i++) {
        arg = va_arg(args, int);
        if (arg < minimum)
            minimum = arg;
    }
    va_end(args);
    return (minimum);
}

///////////////////////////////////////////////////////////////////////////////
float minf(uint n, float x, ...)
{
    float minimum = x;
    float arg;
    va_list args;

    va_start(args, x);
    for (uint i = 0; i < (n - 1); i++) {
        arg = (float)va_arg(args, double);
        if (arg < minimum)
            minimum = arg;
    }
    va_end(args);
    return (minimum);
}

///////////////////////////////////////////////////////////////////////////////
double mind(uint n, double x, ...)
{
    double minimum = x;
    double arg;
    va_list args;

    va_start(args, x);
    for (uint i = 0; i < (n - 1); i++) {
        arg = va_arg(args, double);
        if (arg < minimum)
            minimum = arg;
    }
    va_end(args);
    return (minimum);
}
