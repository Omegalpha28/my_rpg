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
int my_strncmp(cstring s1, cstring s2, size_t n)
{
    if (n == 0)
        return (0);
    do {
        if (*s1 != *s2)
            return (*(custring)s1 - *(custring)s2);
        s2++;
        if (*s1 == 0)
            break;
        s1++;
        --n;
    } while (n != 0);
    return (0);
}
