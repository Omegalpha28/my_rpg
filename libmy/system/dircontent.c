/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** dircontent
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
warray_t my_dircontent(cstring_t path)
{
    u8_t len = my_dirlen(path);
    DIR *dir;
    warray_t content;
    u8_t i = 0;

    RETURN(len == 0 || len == (uchar_t)-1, NULL);
    dir = opendir(path);
    RETURN(dir == NULL, NULL);
    content = malloc(sizeof(string_t) * (len + 1));
    for (struct dirent *info = readdir(dir); info; info = readdir(dir)) {
        if (CMP(info->d_name, ".") || CMP(info->d_name, ".."))
            continue;
        content[i] = my_strdcat(path, "/", info->d_name);
        i++;
    }
    content[len] = 0;
    closedir(dir);
    return (content);
}
