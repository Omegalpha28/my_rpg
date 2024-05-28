/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** loop
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void update_interaction(void)
{
    recti_t pm = Player.ref->self->sheets[Player.ref->sheetId]->image->mask;
    recti_t pr = {Player.ref->position.x - pm.width / 2.0f,
        Player.ref->position.y - pm.height / 2.0f, pm.width, pm.height};
    recti_t ir = {0, 0, 0, 0};
    bool_t hover = false;

    for (uint_t i = 0; i < Pool.interCount && (Time.currentTime -
        Player.lastAction) > 1e3; i++) {
        hover = false;
        ir = Pool.inters[i]->img->mask;
        ir.left = Pool.inters[i]->position.x - ir.width / 2.0f;
        ir.top = Pool.inters[i]->position.y - ir.height / 2.0f;
        hover = sfIntRect_intersects(&ir, &pr, NULL);
        Player.canInteract = hover ? true : Player.canInteract;
        actor_set_anim(Pool.inters[i]->actor, hover ? "hover" : "idle");
        if ((PRESSED(Setting.interact.code) || Pool.inters[i]->type
            == INTERACTABLE_CURRENCY) && Pool.inters[i]->interact != NULL &&
            hover)
            Pool.inters[i]->interact(Pool.inters[i]);
    }
}

///////////////////////////////////////////////////////////////////////////////
static void update(void)
{
    Player.canInteract = false;
    if (!Player.ref->damaged && !Player.ref->dead)
        player_movement();
    check_player_health();
    update_entity();
    update_collisions();
    update_shaking();
    check_shoot();
    cursor_focus();
    update_interaction();
    check_level_end();
}

///////////////////////////////////////////////////////////////////////////////
static void reset_mov(void)
{
    Setting.left.pressed = false;
    Setting.right.pressed = false;
    Setting.up.pressed = false;
    Setting.down.pressed = false;
    Setting.dash.pressed = false;
    Player.velocity = V2F1(0.0f);
}

///////////////////////////////////////////////////////////////////////////////
void game_loop(void)
{
    sfEvent evt;

    Engine.debug.propDrawn = 0;
    while (sfRenderWindow_pollEvent(Win.self, &evt)) {
        parse_events(evt);
        if (evt.type == sfEvtKeyReleased &&
            evt.key.code == Setting.inventory.code)
            Engine.scene = SCENE_INVENTORY;
        if (evt.type == sfEvtKeyReleased &&
            evt.key.code == Setting.pause.code)
            Engine.scene = SCENE_PAUSE;
        CLICK_REL = click_rel(evt);
    }
    if (Player.blocked)
        reset_mov();
    update();
    draw();
    update_all_bullets();
    clear_entity_remove_queue();
}
