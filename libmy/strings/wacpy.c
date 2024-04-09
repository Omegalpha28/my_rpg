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
warray my_wacpy(warray wa)
{
    ulong len = my_walen(wa);
    warray cpy = malloc(sizeof(string) * (len + 1));

    if (cpy == NULL)
        return (NULL);
    for (ulong i = 0; i < len; i++)
        cpy[i] = my_strdup(wa[i]);
    cpy[len] = NULL;
    return (cpy);
}
