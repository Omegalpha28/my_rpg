/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** isfloat
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
bool_t my_isfloat(cstring_t str)
{
    bool_t pts = false;

    if (*str == '-' || *str == '+')
        str++;
    for (; *str; str++) {
        if (*str == '.' && pts == false) {
            pts = true;
            str++;
        }
        RETURN(!(*str >= '0' && *str <= '9'), false);
    }
    return (true);
}
