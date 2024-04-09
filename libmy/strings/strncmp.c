/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** strncmp
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
int my_strncmp(cstring_t s1, cstring_t s2, size_t n)
{
    if (n == 0)
        return (0);
    do {
        if (*s1 != *s2)
            return (*(custring_t)s1 - *(custring_t)s2);
        s2++;
        if (*s1 == 0)
            break;
        s1++;
        --n;
    } while (n != 0);
    return (0);
}
