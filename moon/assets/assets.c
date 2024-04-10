/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** assets
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
struct assets_s Assets = {
    NULL, 0, NULL, 0
};

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets(void)
{
    if (init_assets_creatures() == false)
        return (false);
    printf("Loaded %u images\n", Assets.imageCount);
    printf("Loaded %u creatures\n", Assets.creatureCount);
    for (uint_t i = 0; i < Assets.creatureCount; i++) {
        printf("Creatures[%u]:\n", i);
        printf("\tId: %d\n", Assets.creatures[i]->id);
        printf("\tSheets: %u\n", Assets.creatures[i]->sheetCount);
        for (uint_t j = 0; j < Assets.creatures[i]->sheetCount; j++) {
            sheet_t *sh = Assets.creatures[i]->sheets[j];
            printf("\t\tSheet[%u]\n", j);
            printf("\t\t\tName: '%s'\n", sh->name);
            printf("\t\t\tAnims: %u\n", sh->animCount);
            for (uint_t k = 0; k < sh->animCount; k++) {
                printf("\t\t\t\tName: '%s'\n", sh->anims[k]->name);
            }
            printf("\t\t\tVariants: %u\n", sh->variantCount);
        }
        printf("\tMiscs: %u\n", Assets.creatures[i]->miscCount);
        for (uint_t j = 0; j < Assets.creatures[i]->miscCount; j++)
            printf("\t\tName: '%s'\n", Assets.creatures[i]->miscs[j]->name);
    }
    return (true);
}
