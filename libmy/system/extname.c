/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** extname
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
string_t my_extname(cstring_t path)
{
    string_t ext = my_strrchr(path, '.');

    if (ext == NULL)
        return (NULL);
    if (my_strlen(ext) <= 1 || my_strlen(ext) > MAX_EXTENSION_LENGTH)
        return (NULL);
    return (ext + 1);
}
