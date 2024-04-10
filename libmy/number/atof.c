/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** atof
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
double my_atof(cstring_t str)
{
    int pi = 0;
    int pf = 0;
    cstring_t s = NULL;

    RETURN(*str == '\0', 0.0f);
    pi = my_strtol(str, &str);
    if (*str == '.') {
        str++;
        s = str;
        pf = my_strtol(str, &str);
        return ((double)pi + ((double)pf) / pow(10, my_strlen(s)));
    }
    return ((double)pi);
}
