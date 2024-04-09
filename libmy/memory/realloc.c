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
void *my_realloc(void *ptr, ulong size)
{
    void *new_ptr = NULL;

    if (size == 0)
        return (NULL);
    new_ptr = malloc(size);
    if (new_ptr && ptr) {
        my_memcpy(new_ptr, ptr, size);
        free(ptr);
    }
    return (new_ptr);
}
