/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** error
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
bool_t my_error(cstring_t err)
{
    my_puterr("Error: ");
    my_puterr(err);
    my_puterr("\n");
    return (false);
}
