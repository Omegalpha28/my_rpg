/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** strdup
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
string_t my_strndup(cstring_t str, ulong_t n)
{
    ulong_t len = my_strlen(str) + 1;
    string_t copy;

    len = (n + 1) > len ? len : (n + 1);
    copy = malloc((uint_t)len);
    RETURN(!copy, NULL);
    my_memcpy(copy, str, len);
    copy[len - 1] = 0;
    return (copy);
}
