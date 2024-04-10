/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** atob
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
bool_t my_atob(cstring_t str)
{
    int len = my_strlen(str);

    RETURN(len == 1, str[0] - '0');
    RETURN((!my_strcmp(str, "FALSE") || !my_strcmp(str, "false")), false);
    RETURN((!my_strcmp(str, "FALSE)") || !my_strcmp(str, "false)")), false);
    RETURN((!my_strcmp(str, "TRUE") || !my_strcmp(str, "true")), true);
    RETURN((!my_strcmp(str, "TRUE)") || !my_strcmp(str, "true)")), true);
    return (false);
}
