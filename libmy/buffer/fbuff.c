/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** fbuff
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
bool_t my_fbuff(buffer_t *buffer, cstring_t path)
{
    FILE *fd = fopen(path, "wb");

    if (fd == NULL)
        return (false);
    fwrite(buffer->content, sizeof(char), buffer->size, fd);
    fclose(fd);
    return (true);
}
