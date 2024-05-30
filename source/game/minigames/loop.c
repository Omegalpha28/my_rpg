/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** get_baby
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
static void grow_interactable(void)
{
    Assets.axolotl[Engine.axo_minigame]->grown++;
    for (uint_t i = 0; i < Pool.interCount; i++) {
        if (Pool.inters[i]->type != INTERACTABLE_EGG || Pool.inters[i]->data[0]
            != (int)(Engine.axo_minigame - 1))
            continue;
        if (Assets.axolotl[Engine.axo_minigame]->grown == AXO_TEEN)
            actor_set_sheet(Pool.inters[i]->actor, "teenagers");
        if (Assets.axolotl[Engine.axo_minigame]->grown == AXO_ADULT)
            actor_set_sheet(Pool.inters[i]->actor, "adults");
    }
}

///////////////////////////////////////////////////////////////////////////////
static void set_music_of_level(void)
{
    sfMusic *music = find_music("by-the-campfire");

    end_music();
    sfMusic_setVolume(music, clampf(Setting.master *
        (Setting.music / 100.0f) * 0.75f, 0.0f, 100.0f));
    sfMusic_play(music);
}

///////////////////////////////////////////////////////////////////////////////
static void minigame_1(void)
{
    draw_text_center(ROT, V2F(Win.width / 2, Win.height / 8), 0.45f, sfWhite);
    if (CLICK_REL && Engine.click != -1) {
        Engine.click++;
        sfx(SFX_PAT);
    }
    if (Engine.click == 10) {
        search_and_destroy("smile");
        if (!is_effect("blech"))
            effect("blech", V2F(0.0f, 10.0f), false);
        sfx(SFX_BURP);
        Engine.click = -1;
    }
    if (Engine.click == -1 && !is_effect("blech")) {
        Engine.scene = SCENE_GAME;
        sfView_setCenter(Win.view, Player.shakeOffset);
        Engine.click = 0;
        sfRenderWindow_setView(Win.self, Win.view);
        grow_interactable();
        set_music_of_level();
    }
}

///////////////////////////////////////////////////////////////////////////////
void get_baby(interactable_t *obj)
{
    uint_t roll = rand() % 3;
    sfMusic *music = find_music("baby-xolotl");

    end_music();
    Engine.roll = roll;
    Engine.axo_minigame = obj->data[0] + 1;
    Engine.scene = SCENE_MINIGAME;
    Player.shakeOffset = sfView_getCenter(Win.view);
    sfMusic_setVolume(music, clampf(Setting.master *
        (Setting.music / 100.0f) * 0.75f, 0.0f, 100.0f));
    sfMusic_play(music);
    sfView_setCenter(Win.view, V2F1(0.0f));
    sfRenderWindow_setView(Win.self, Win.view);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_baby(void)
{
    sfSprite *baby = sfSprite_create();
    recti_t mask = Assets.babies[Engine.axo_minigame]->mask;
    sfIntRect rect = {0, 0, mask.width, mask.height - 30.0f};

    sfSprite_setTexture(baby, Assets.babies[Engine.axo_minigame]->self, false);
    sfSprite_setTextureRect(baby, rect);
    sfSprite_setOrigin(baby, V2F(mask.width / 2, mask.height / 2 - 30.0f));
    sfSprite_setPosition(baby, PX_TO_MAPF(V2F(Win.width / 2, Win.height / 2)));
    sfRenderWindow_drawSprite(Win.self, baby, false);
    if (!is_effect("smile") && Engine.click != -1)
        effect("smile", V2F(0.0f, 10.0f), false);
    sfSprite_destroy(baby);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_bacs(void)
{
    v2f_t pos = {0.0f, 0.0f};
    sfRectangleShape *shadow = sfRectangleShape_create();
    sfSprite *pattern = sfSprite_create();

    sfRectangleShape_setPosition(shadow, PX_TO_MAPF(pos));
    sfRectangleShape_setSize(shadow, V2F(Win.width, Win.height));
    sfRectangleShape_setFillColor(shadow, RGB(121, 167, 202));
    sfRenderWindow_drawRectangleShape(Win.self, shadow, false);
    sfSprite_setTexture(pattern, Assets.ui[UI_PATTERN_AXO]->self, false);
    sfSprite_setColor(pattern, RGB(113, 152, 201));
    for (uint_t i = 0; i < 30; i++) {
        sfSprite_setPosition(pattern, PX_TO_MAPF(V2F(i % 4 * 130 * Win.width /
            Win.viewWidth, (i - i % 4) * 12 * Win.height / Win.viewHeight)));
        sfRenderWindow_drawSprite(Win.self, pattern, false);
    }
    sfRectangleShape_destroy(shadow);
}

///////////////////////////////////////////////////////////////////////////////
static void parse_minigame_events(void)
{
    sfEvent evt;

    while (sfRenderWindow_pollEvent(Win.self, &evt)) {
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
        CLICK_REL = click_rel(evt);
        if (evt.type == sfEvtKeyReleased &&
            evt.key.code == Setting.pause.code) {
            Engine.scene = SCENE_GAME;
            sfView_setCenter(Win.view, Player.shakeOffset);
            sfRenderWindow_setView(Win.self, Win.view);
            search_and_destroy("smile");
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
void minigame_loop(void)
{
    CLICK_REL = false;
    parse_minigame_events();
    draw_bacs();
    draw_baby();
    minigame_1();
    for (uint_t i = 0; i < Pool.effectCount; i++)
        if (CMP(Pool.effects[i]->self->name, "smile") ||
            CMP(Pool.effects[i]->self->name, "blech"))
            effect_draw(Pool.effects[i]);
    draw_cursor();
}
