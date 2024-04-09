/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** realloc
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
void *my_orealloc(void *ptr, ulong old_size, ulong new_size)
{
    void *new_ptr = NULL;

    if (new_size == 0)
        return (NULL);
    if (new_size == old_size)
        return (ptr);
    new_ptr = malloc(new_size);
    if (new_ptr && ptr) {
        my_memcpy(new_ptr, ptr, old_size);
        free(ptr);
    }
    return (new_ptr);
}
