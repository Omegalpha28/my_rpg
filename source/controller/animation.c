/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** animation
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static effect_t *search_effect(cstring_t name)
{
    for (uint_t i = 0; i < Pool.effectCount; i++) {
        if (CMP(Pool.effects[i]->self->name, name))
            return (Pool.effects[i]);
    }
    return (NULL);
}

///////////////////////////////////////////////////////////////////////////////
void use_competence(void)
{
    if (!HEAL || Player.velocity.x != 0.0f || Player.velocity.y != 0.0f ||
        DANCE || DASH || Player.ref->charges != 5 || Player.ref->health ==
        (int)Assets.axolotl[Player.ref->variantId]->maxHealth) {
        HEAL = false;
        if (!(search_effect("snack") != NULL && Player.ref->charges == 0))
            effect_destroy(search_effect("snack"));
        return;
    }
    if (search_effect("snack") == NULL)
        sfSprite_setScale(effect("snack", Player.ref->position, false)->sprite,
            V2F1(0.5f));
    actor_set_anim(Player.ref, "eat");
    if ((Time.currentTime - Player.ref->time) > (DEFAULT_CREATURE_FR * 12)) {
        Player.ref->health++;
        Player.ref->charges = 0;
        HEAL = false;
        sfx(SFX_HEALTH);
        actor_set_anim(Player.ref, "idle");
    }
}

///////////////////////////////////////////////////////////////////////////////
static void check_player_regenerate(void)
{
    if (!Player.blocked || !Player.ref->done)
        return;
    Player.blocked = false;
}

///////////////////////////////////////////////////////////////////////////////
void player_movement(void)
{
    Player.velocity = (v2f_t){0.0f, 0.0f};
    if (UP && !DANCE && !DASH)
        Player.velocity.y += -SPEED;
    if (DOWN && !DANCE && !DASH)
        Player.velocity.y += SPEED;
    if (LEFT && !DANCE && !DASH)
        Player.velocity.x += -SPEED;
    if (RIGHT && !DANCE && !DASH)
        Player.velocity.x += SPEED;
    get_last_input();
    Player.velocity = multiply2f(multiply2f(normalize2f(Player.velocity),
        V2F1(Time.deltaTime / 15)), V2F1(SPEEDF));
    if (!DASH && !DANCE && !HEAL && !Player.blocked)
        actor_set_anim(Player.ref, (Player.velocity.x != 0.0f ||
            Player.velocity.y != 0.0f) ? "walk" : "idle");
    check_player_regenerate();
    if (DANCE)
        actor_set_anim(Player.ref, "dance");
    dash_movement();
    use_competence();
}

///////////////////////////////////////////////////////////////////////////////
static void dash_animation(void)
{
    v2f_t velocity = Player.last_velocity;

    actor_set_anim(Player.ref, "dash");
    if (!Player.ref->done) {
        if ((UP && velocity.y < 0.0f) || velocity.y < 0.0f)
            Player.velocity.y += -SPEED;
        if ((DOWN && velocity.y > 0.0f) || velocity.y > 0.0f)
            Player.velocity.y += SPEED;
        if ((LEFT && velocity.x < 0.0f) || velocity.x < 0.0f)
            Player.velocity.x += -SPEED;
        if ((RIGHT && velocity.x > 0.0f) || velocity.x > 0.0f)
            Player.velocity.x += SPEED;
        Player.velocity = multiply2f(multiply2f(normalize2f(Player.velocity),
            V2F1(Time.deltaTime / (10 + (8 * (clamp(Player.ref->frame - 26, 0,
                99)))))), V2F1(SPEEDF));
        actor_move(Player.ref, Player.velocity);
        Player.ref->scale.x = Player.velocity.x < 0.0f ? -1.0f : 1.0f;
        camera_move();
    }
}

///////////////////////////////////////////////////////////////////////////////
void dash_movement(void)
{
    v2f_t cr = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));

    Player.ref->scale.x = Player.ref->position.x > cr.x ? -1.0f : 1.0f;
    if (DASH && !DANCE) {
        if (!CMP(Player.ref->self->sheets[Player.ref->sheetId]->
            anims[Player.ref->animId]->name, "dash"))
            sfx(SFX_PLAYER_DASH);
        dash_animation();
    }
    if (Player.ref->done && !DANCE && DASH) {
        actor_set_anim(Player.ref, (Player.velocity.x != 0.0f ||
            Player.velocity.y != 0.0f) ? "walk" : "idle");
        DASH = false;
    }
    actor_move(Player.ref, multiply2f(Player.velocity, V2F1(Player.speed)));
    camera_move();
}
