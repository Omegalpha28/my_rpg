/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** strlen
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
ulong_t my_strlen(cstring_t s)
{
    cstring_t a = s;
    const ulong_t *w;

    for (; (unsigned long int)s % ALIGN; s++)
        if (!*s)
            return (s - a);
    for (w = (const void *)s; !HASZERO(*w); w++);
    for (s = (const void *)w; *s; s++);
    return (s - a);
}
