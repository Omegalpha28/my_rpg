/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** wacpy
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
warray_t my_wacpy(warray_t wa)
{
    ulong_t len = my_walen(wa);
    warray_t cpy = malloc(sizeof(string_t) * (len + 1));

    if (cpy == NULL)
        return (NULL);
    for (ulong_t i = 0; i < len; i++)
        cpy[i] = my_strdup(wa[i]);
    cpy[len] = NULL;
    return (cpy);
}
