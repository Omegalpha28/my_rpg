/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** categories
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static sheet_t *create_sheet(category_t *cat, cstring_t path)
{
    sheet_t *sheet = (sheet_t *)malloc(sizeof(sheet_t));

    sheet->anims = NULL;
    sheet->animCount = 0;
    sheet->name = NULL;
    sheet->image = add_image(path, false, (v2u_t){1, 1}, "PLACEHOLDER");
    sheet->variantCount = 0;
    sheet->variants = NULL;
    cat->sheetCount++;
    cat->sheets = REALLOC(cat->sheets, sizeof(sheet_t *), cat->sheetCount);
    cat->sheets[cat->sheetCount - 1] = sheet;
    return (sheet);
}

///////////////////////////////////////////////////////////////////////////////
static bool_t create_item_animation(sheet_t *sheet, bool_t autplay)
{
    animation_t *anim = (animation_t *)malloc(sizeof(animation_t));

    sheet->animCount = 1;
    sheet->anims = (animation_t **)malloc(sizeof(animation_t *));
    sheet->anims[0] = anim;
    anim->endingFrame = sheet->image->grid.x - 1;
    anim->startingFrame = 0;
    anim->looped = autplay;
    anim->name = my_strdup("default");
    anim->frameCount = sheet->image->grid.x;
    anim->frameRate = DEFAULT_PROP_FR;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
static bool_t create_category_item(category_t *cat, cstring_t path)
{
    sheet_t *sheet = create_sheet(cat, path);
    string_t name = my_strndup(my_basename(path), my_strlen(my_basename(path))
        - my_strlen(my_extname(my_basename(path))) - 1);
    warray_t wa = my_strsplit(my_basename(name), '-');

    FREE(name);
    if (!wa || wa[0][1] != '\0' || (wa[0][0] == 'S' && my_walen(wa) != 2) ||
        (wa[0][0] == 'A' && (my_walen(wa) != 5 || !my_isint(wa[2]) ||
        !my_isint(wa[3]) || !my_isbool(wa[4])))) {
        my_watroy(wa);
        return (my_error(ERR_SHEET_SYNTAX));
    }
    sheet->name = my_strdup(wa[1]);
    if (wa[0][0] == 'A') {
        sheet->image->grid.x = my_atoi(wa[2]);
        sheet->image->grid.y = my_atoi(wa[3]);
        create_item_animation(sheet, my_atob(wa[4]));
    }
    my_watroy(wa);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
static category_t *create_category(zone_t *zone, cstring_t path)
{
    category_t *cat = (category_t *)malloc(sizeof(category_t));

    cat->name = my_strdup(my_basename(path));
    cat->sheetCount = 0;
    cat->sheets = NULL;
    cat->type = catOther;
    zone->categoryCount++;
    zone->categories = REALLOC(zone->categories, sizeof(category_t *),
        zone->categoryCount);
    zone->categories[zone->categoryCount - 1] = cat;
    if (CMP(cat->name, CAT_DESTRUCTIBLE))
        cat->type = catDestructible;
    if (CMP(cat->name, CAT_DOOR))
        cat->type = catDoors;
    if (CMP(cat->name, CAT_TRAP))
        cat->type = catTraps;
    return (cat);
}

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_category(zone_t *zone, cstring_t path)
{
    warray_t content = my_dircontent(path);
    category_t *cat = NULL;
    bool_t success = true;

    if (content == NULL)
        return (true);
    cat = create_category(zone, path);
    for (uint_t i = 0; success && content[i]; i++) {
        if (my_isdir(content[i]) == true && my_extname(content[i]) != NULL)
            continue;
        success = create_category_item(cat, content[i]);
    }
    my_watroy(content);
    return (success);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_assets_category(category_t *cat)
{
    if (cat == NULL)
        return;
    return;
}
