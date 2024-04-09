/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** strtok_r
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
string_t my_strtok_r(string_t s, cstring_t delim, string_t *save_ptr)
{
    string_t token;

    if (s == NULL)
        s = *save_ptr;
    s += my_strspn(s, delim);
    if (*s == '\0') {
        *save_ptr = s;
        return (NULL);
    }
    token = s;
    s = my_strpbrk(token, delim);
    if (s == NULL)
        *save_ptr = my_strchr(token, '\0');
    else {
        *s = '\0';
        *save_ptr = s + 1;
    }
    return (token);
}
