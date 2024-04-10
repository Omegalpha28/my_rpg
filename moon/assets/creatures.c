/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** creatures
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static bool_t creature_parse_operator(cstring_t op, assets_creatures_t *crt)
{
    if (crt->status == entryNothing && (!my_strncmp(op, "[START-", 7) &&
        my_countchar(op, ']') == 1)) {
        crt->sheetCount++;
        crt->sheets = REALLOC(crt->sheets, sizeof(sheet_t *), crt->sheetCount);
        crt->sheets[crt->sheetCount - 1] = (sheet_t *)malloc(sizeof(sheet_t));
        crt->sheets[crt->sheetCount - 1]->animCount = 0;
        crt->sheets[crt->sheetCount - 1]->anims = NULL;
        crt->sheets[crt->sheetCount - 1]->variantCount = 0;
        crt->sheets[crt->sheetCount - 1]->variants = NULL;
        crt->sheets[crt->sheetCount - 1]->image = NULL;
        crt->sheets[crt->sheetCount - 1]->name = my_strndup((op + 7),
            my_strwlen((op + 7), ']'));
        crt->status = entrySheet;
        return (true);
    }
    if (!my_strncmp(op, "[END]", 5) || !my_strncmp(op, "[MISC]", 6)) {
        crt->status = !my_strncmp(op, "[END]", 5) ? entryNothing : entryMisc;
        return (true);
    }
    return (false);
}

///////////////////////////////////////////////////////////////////////////////
static bool_t creature_parse_anim(warray_t wa, assets_creatures_t *crt)
{
    sheet_t *sh = NULL;
    animation_t *anim;

    if (crt->status != entrySheet)
        return (false);
    sh = crt->sheets[crt->sheetCount - 1];
    if (!my_isint(wa[1]) || !my_isint(wa[2]) || (!my_isint(wa[3]) &&
        !CMP(wa[3], "DEFAULT")) || !my_isbool(wa[4]))
        return (false);
    anim = (animation_t *)malloc(sizeof(animation_t));
    anim->name = my_strdup(wa[0]);
    anim->startingFrame = my_atoi(wa[1]);
    anim->endingFrame = my_atoi(wa[2]);
    anim->frameRate = my_isint(wa[3]) ? my_atoi(wa[3]) : DEFAULT_CREATURE_FR;
    anim->looped = my_atob(wa[4]);
    sh->animCount++;
    sh->anims = REALLOC(sh->anims, sizeof(animation_t *), sh->animCount);
    sh->anims[sh->animCount - 1] = anim;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
static bool_t add_image_to_sheet(image_t *img, assets_creatures_t *crt)
{
    sheet_t *sh = crt->sheets[crt->sheetCount - 1];

    if (sh->image == NULL) {
        sh->image = img;
        return (true);
    }
    sh->variantCount++;
    sh->variants = REALLOC(sh->variants, sizeof(image_t *), sh->variantCount);
    sh->variants[sh->variantCount - 1] = img;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
static bool_t creature_parse_texture(warray_t wa, assets_creatures_t *crt)
{
    if (crt->status == entryNothing || !my_isint(wa[0]) || !my_isint(wa[1]) ||
        !my_isint(wa[2]) || !add_image(wa[4], true, (v2u_t){my_atoi(wa[0]),
        my_atoi(wa[1])}, wa[3]))
        return (false);
    if (crt->status == entrySheet)
        return (add_image_to_sheet(Assets.images[Assets.imageCount - 1], crt));
    crt->miscCount++;
    crt->miscs = REALLOC(crt->miscs, sizeof(image_t *), crt->miscCount);
    crt->miscs[crt->miscCount - 1] = Assets.images[Assets.imageCount - 1];
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
static bool_t creature_parse_id(cstring_t id, assets_creatures_t *crt)
{
    if (!my_isint(id))
        return (false);
    crt->id = my_atoi(id);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
static bool_t creature_parse_line(string_t line, assets_creatures_t *crt)
{
    warray_t wa = my_stowa(line);
    ulong_t len = wa ? my_walen(wa) : 0;
    bool_t success = false;

    if (wa == NULL)
        return (false);
    if (len == 1 && wa[0][0] == '[')
        success = creature_parse_operator(wa[0], crt);
    else if (len == 1)
        success = creature_parse_id(wa[0], crt);
    if (len == 5 && my_isbool(wa[4]))
        success = creature_parse_anim(wa, crt);
    else if (len == 5)
        success = creature_parse_texture(wa, crt);
    my_watroy(wa);
    return (success);
}

///////////////////////////////////////////////////////////////////////////////
static bool_t creature_parse(cstring_t path, assets_creatures_t *crt)
{
    FILE *fd = fopen(path, "r");
    string_t ln = NULL;
    ulong_t len = 0;
    bool_t success = true;
    string_t tmp = NULL;

    if (fd == NULL)
        return (false);
    for (long read = getline(&ln, &len, fd); success && read != -1;
        read = getline(&ln, &len, fd)) {
        for (tmp = ln; tmp && my_isspace(*tmp); tmp++);
        if (!tmp || tmp[0] == '\0' || tmp[0] == '#')
            continue;
        success = creature_parse_line(tmp, crt);
    }
    FREE(ln);
    fclose(fd);
    return (success);
}

///////////////////////////////////////////////////////////////////////////////
static void init_creature(assets_creatures_t *crt)
{
    if (crt == NULL)
        return;
    crt->miscCount = 0;
    crt->miscs = NULL;
    crt->sheetCount = 0;
    crt->sheets = NULL;
    crt->status = entryNothing;
}

///////////////////////////////////////////////////////////////////////////////
static bool_t add_creature(warray_t ctn)
{
    assets_creatures_t *crt = malloc(sizeof(assets_creatures_t));
    bool_t success = false;

    init_creature(crt);
    for (uint_t i = 0; crt != NULL && ctn[i]; i++) {
        if (my_isdir(ctn[i]) == true)
            continue;
        if (my_extname(ctn[i]) && CMP(my_extname(ctn[i]), EXT_CREATURE)) {
            success = creature_parse(ctn[i], crt);
            break;
        }
    }
    if (success) {
        Assets.creatureCount++;
        Assets.creatures = my_orealloc(Assets.creatures,
            sizeof(assets_creatures_t *) * (Assets.creatureCount - 1),
            sizeof(assets_creatures_t *) * Assets.creatureCount);
        Assets.creatures[Assets.creatureCount - 1] = crt;
    }
    return (success);
}

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_creatures(void)
{
    warray_t content = my_dircontent(DIR_CREATURES);
    warray_t subcontent = NULL;
    bool_t success = true;

    if (content == NULL)
        return (false);
    for (uint_t i = 0; content[i]; i++) {
        if (my_isdir(content[i]) == false)
            continue;
        subcontent = my_dircontent(content[i]);
        if (subcontent == NULL)
            continue;
        success = add_creature(subcontent);
        my_watroy(subcontent);
        if (!success)
            break;
    }
    my_watroy(content);
    return (success);
}
