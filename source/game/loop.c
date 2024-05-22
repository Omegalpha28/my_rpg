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
static void check_shoot(void)
{
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    bool_t pressed = MPRESSED(Setting.shoot);
    uint_t reload_time = WEAPON_STATS[Player.weapon].reload_time * 1000;
    uint_t firerate = WEAPON_STATS[Player.weapon].firerate * 1000;

    if (!pressed || DANCE || DASH ||
        (Time.currentTime - Player.shoot_time) < firerate ||
        ((Time.currentTime - Player.shoot_time) < reload_time &&
        Player.num_shoot > WEAPON_STATS[Player.weapon].ammoPerMag))
        return;
    Player.num_shoot++;
    if (!((Time.currentTime - Player.shoot_time) < reload_time) &&
        Player.num_shoot > WEAPON_STATS[Player.weapon].ammoPerMag)
        Player.num_shoot = 0;
    if (Player.num_shoot == WEAPON_STATS[Player.weapon].ammoPerMag &&
        WEAPON_STATS[Player.weapon].bulletType != BULLET_MELEE)
        return;
    Player.shoot_time = Time.currentTime;
    create_bullet(Player.ref, cr, Player.weapon);
}

///////////////////////////////////////////////////////////////////////////////
static void update(void)
{
    if (!Player.ref->damaged && !Player.ref->dead)
        player_movement();
    check_player_health();
    update_entity();
    update_collisions();
    update_shaking();
    check_shoot();
    cursor_focus();
    check_level_end();
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
    update();
    draw();
    update_all_bullets();
    clear_entity_remove_queue();
}
