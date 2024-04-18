/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** buffint
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "my.h"

///////////////////////////////////////////////////////////////////////////////
void my_buffint(buffer_t *buffer, int value, uint_t bytes)
{
    for (; (bytes - 1) > 0; bytes--)
        my_buffchar(buffer, (value >> (8 * (bytes - 1))) & 255);
    my_buffchar(buffer, (value) & 255);
}
