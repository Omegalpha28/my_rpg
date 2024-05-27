/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** end
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static string_t DOORS[] = {
    "exit_door_boss_bottom",
    "exit_door_1",
    "exit_door_2",
    "exit_door_bottom",
    "transition_door_bottom",
    "door",
    "entrance_door",
    "entrance",
    NULL
};

///////////////////////////////////////////////////////////////////////////////
void clear_entity_remove_queue(void)
{
    for (uint_t i = 0; i < ENTITY_REMOVE; i++) {
        if (Entities.toRemove[i] != NULL)
            remove_entity(Entities.toRemove[i]);
        Entities.toRemove[i] = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
static void check_opening_animation(void)
{
    float maxY = 0.0f;

    if (Entities.count != 0)
        return;
    for (uint_t i = 0; i < Pool.propCount; i++) {
        if (!CMP(Pool.props[i]->self->name, "plank_door") && !CMP(
            Pool.props[i]->self->name, "entrance_door"))
            continue;
        if (Pool.props[i]->position.y < maxY)
            maxY = Pool.props[i]->position.y;
        prop_animate(Pool.props[i]);
    }
    if (Engine.level > 1 && Engine.level != 3)
        spawn_interactable(INTERACTABLE_CHEST, V2F(0.0f, maxY + 50.0f),
            0, &openchest);
    Entities.count = -1;
}

///////////////////////////////////////////////////////////////////////////////
static prop_t **get_doors_prop(uint_t *n)
{
    prop_t **doors = NULL;

    for (uint_t i = 0; i < Pool.propCount; i++) {
        if (!my_wacmp(DOORS, (string_t)Pool.props[i]->self->name))
            continue;
        (*n)++;
        doors = REALLOC(doors, sizeof(prop_t *), (*n));
        doors[(*n) - 1] = Pool.props[i];
    }
    return (doors);
}

///////////////////////////////////////////////////////////////////////////////
static void go_through_door(prop_t *prop)
{
    if (CMP(prop->self->name, "door"))
        Engine.level = 9;
    Engine.level++;
    switch_level();
}

///////////////////////////////////////////////////////////////////////////////
static void check_door_collision(prop_t *prop)
{
    v2f_t ppos = Player.ref->position;
    recti_t pmask = Player.ref->self->sheets[Player.ref->sheetId]->image->mask;
    v2f_t dpos = prop->position;
    recti_t dmask = prop->self->image->mask;
    rectf_t player = {ppos.x - pmask.width / 2.0f, ppos.y
        , pmask.width, pmask.height / 2.0f};
    rectf_t door = {dpos.x - dmask.width / 4.0f, dpos.y - dmask.height / 2.0f,
        dmask.width / 2.0f, dmask.height / 1.5f};

    if (sfFloatRect_intersects(&player, &door, NULL))
        go_through_door(prop);
}

///////////////////////////////////////////////////////////////////////////////
void check_level_end(void)
{
    prop_t **doors = NULL;
    uint_t n = 0;

    if (Entities.count > 0 || (Engine.level == 3 && Player.ref->charges > 4))
        return;
    check_opening_animation();
    doors = get_doors_prop(&(n));
    for (uint_t i = 0; i < n && Entities.count == -1; i++)
        check_door_collision(doors[i]);
    FREE(doors);
}
