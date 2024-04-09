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
string my_strndup(cstring str, ulong n)
{
    ulong len = my_strlen(str) + 1;
    string copy;

    len = (n + 1) > len ? len : (n + 1);
    copy = malloc((uint)len);
    RETURN(!copy, NULL);
    my_memcpy(copy, str, len);
    copy[len - 1] = 0;
    return (copy);
}
