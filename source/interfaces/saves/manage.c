/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** manage
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void check_save_folder(void)
{
    struct stat st = {0};

    if (stat("playerData", &st) == -1)
        mkdir("playerData", 0700);
}

///////////////////////////////////////////////////////////////////////////////
void delete_save(uint_t id)
{
    char filename[32];

    if (id > 3)
        return;
    snprintf(filename, 32, "playerData/save%u.bin", id);
    if (!exist_save(id))
        return;
    remove(filename);
}

///////////////////////////////////////////////////////////////////////////////
bool_t exist_save(uint_t id)
{
    char filename[32];
    struct stat st = {0};

    if (id > 3)
        return (false);
    snprintf(filename, 32, "playerData/save%u.bin", id);
    if (stat(filename, &st) == -1)
        return (false);
    return (true);
}
