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
static void sort(warray_t arr)
{
    uint_t i = 0;
    string_t tmp = NULL;

    if (arr == NULL || arr[0] == NULL)
        return;
    while (arr[i] && arr[i + 1]) {
        if (strcmp(my_basename(arr[i]), my_basename(arr[i + 1])) > 0) {
            tmp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = tmp;
            i = 0;
        } else
            i++;
    }
}

///////////////////////////////////////////////////////////////////////////////
warray_t my_dircontent(cstring_t path)
{
    ulong_t len = my_dirlen(path);
    DIR *dir;
    warray_t content;
    ulong_t i = 0;

    RETURN(len == 0 || len == (ulong_t)-1, NULL);
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
    sort(content);
    return (content);
}
