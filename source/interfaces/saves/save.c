/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** save
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void save_save_data(FILE *fd)
{
    Assets.axolotl[0]->grown = AXO_ADULT;
    for (uint_t i = 0; i < AXO_COUNT; i++)
        fprintf(fd, "%d ", Assets.axolotl[i]->grown);
    fprintf(fd, "\n");
    fprintf(fd, "%u %u %u %u %u %u %u %u %u %u %u\n",
        Player.purse.cookies, Player.purse.doraditos,
        Player.purse.doraditosBlue, Player.purse.eldritchMeats,
        Player.purse.fishs, Player.purse.happiness,
        Player.purse.honeyCombs, Player.purse.lettuces,
        Player.purse.mushrooms, Player.purse.salts,
        Player.purse.gems);
}

///////////////////////////////////////////////////////////////////////////////
void save_save(uint_t id)
{
    char filename[32];
    FILE *fd = NULL;

    if (id > 3)
        return;
    snprintf(filename, 32, "playerData/save%u.bin", id);
    check_save_folder();
    fd = fopen(filename, "w+");
    if (fd == NULL)
        return;
    save_save_data(fd);
    fclose(fd);
}
