/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** isbool
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
bool_t my_isbool(cstring_t str)
{
    int len = my_strlen(str);

    if (len == 1 || (len == 2 && str[1] == ')')) {
        RETURN(str[0] == '0' || str[0] == '1', true);
        return (false);
    }
    if (my_strcmp(str, "FALSE") == 0 || my_strcmp(str, "TRUE") ||
        my_strcmp(str, "true") || my_strcmp(str, "false"))
        return (true);
    if (my_strcmp(str, "FALSE)") == 0 || my_strcmp(str, "TRUE)") ||
        my_strcmp(str, "true)") || my_strcmp(str, "false)"))
        return (true);
    return (false);
}
