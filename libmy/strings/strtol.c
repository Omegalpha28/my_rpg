/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** strtol
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
int my_strtol(cstring_t s, cstring_t *ptr)
{
    ulong_t i = 0;
    int n = 0;
    bool_t sign = false;

    for (; my_isspace(s[i]); i++);
    if (s[i] == '-') {
        i++;
        sign = true;
    }
    while (my_isdigit(s[i])) {
        n = (n * 10) + (s[i] - '0');
        i++;
    }
    (*ptr) = (*ptr + i);
    return (sign ? -n : n);
}
