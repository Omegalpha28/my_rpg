/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** load
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void load_save_data(FILE *fd)
{
    int tmp = 0;

    for (uint_t i = 0; i < AXO_COUNT; i++) {
        fscanf(fd, "%d ", &(tmp));
        Assets.axolotl[i]->grown = tmp;
    }
    fscanf(fd, "\n");
    fscanf(fd, "%u %u %u %u %u %u %u %u %u %u %u\n",
        &(Player.purse.cookies), &(Player.purse.doraditos),
        &(Player.purse.doraditosBlue), &(Player.purse.eldritchMeats),
        &(Player.purse.fishs), &(Player.purse.happiness),
        &(Player.purse.honeyCombs), &(Player.purse.lettuces),
        &(Player.purse.mushrooms), &(Player.purse.salts),
        &(Player.purse.gems));
}

///////////////////////////////////////////////////////////////////////////////
void load_save(uint_t id)
{
    FILE *fd = NULL;
    char filename[32];

    check_save_folder();
    if (!exist_save(id))
        return;
    snprintf(filename, 32, "playerData/save%u.bin", id);
    fd = fopen(filename, "r");
    if (fd == NULL)
        return;
    load_save_data(fd);
    fclose(fd);
}
