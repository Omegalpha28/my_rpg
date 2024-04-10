/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** isint
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
bool_t my_isint(cstring_t str)
{
    bool_t intEnded = false;

    for (; str && my_isspace(*str); str++);
    if (*str == '-' || *str == '+')
        str++;
    for (; *str; str++) {
        if (my_isdigit(*str) && !intEnded)
            continue;
        if (my_isspace(*str) && !intEnded) {
            intEnded = true;
            continue;
        }
        if (!my_isspace(*str))
            return (false);
    }
    return (true);
}
