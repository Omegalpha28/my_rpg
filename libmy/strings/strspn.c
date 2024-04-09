/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** strspn
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
ulong_t my_strspn(cstring_t s1, cstring_t s2)
{
    cstring_t s = s1;
    cstring_t c;

    while (*s1) {
        for (c = s2; *c && !(*s1 == *c); c++);
        if (*c == '\0')
            break;
        s1++;
    }
    return (s1 - s);
}