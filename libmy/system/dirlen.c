/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** dirlen
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
u8_t my_dirlen(cstring_t path)
{
    DIR *dir = opendir(path);
    u8_t count = 0;

    if (dir == NULL)
        return ((u8_t)-1);
    for (struct dirent *info = readdir(dir); info; info = readdir(dir)) {
        if (CMP(info->d_name, ".") || CMP(info->d_name, ".."))
            continue;
        count++;
    }
    closedir(dir);
    return (count);
}
