/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** loop
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

static void functions(int butt)
{
    if (CLICK_REL && butt == 1)
        Engine.scene = SCENE_GAME;
    if (CLICK_REL && butt == 2)
        Engine.scene = SCENE_INVENTORY;
    if (CLICK_REL && butt == 3)
        Engine.scene = SCENE_SETTINGS;
    if (CLICK_REL && butt == 4)
        Engine.scene = SCENE_MAIN_MENU;
    if (CLICK_REL && butt == 5) {
        Engine.level -= Engine.level % 10;
        if (Engine.level == 0)
            Engine.level++;
        switch_level();
        Engine.scene = SCENE_GAME;
    }
    if (CLICK_REL && butt == 6) {
        Engine.level = 0;
        switch_level();
    }
}

static sfColor get_color(v2f_t pos, int butt)
{
    v2f_t mouse = PX_TO_MAPF(sfMouse_getPositionRenderWindow(Win.self));
    sfSprite *select;

    RETURN(mouse.x > 50 || mouse.x < -25, sfWhite);
    RETURN(!(mouse.y >= (pos.y - 5) && mouse.y <= (pos.y + 15)), sfWhite);
    Setting.hover = true;
    select = sfSprite_create();
    sfSprite_setTexture(select, Assets.ui[UI_DUAL_MARK_SMALL]->self, false);
    sfSprite_setPosition(select, V2F(pos.x - 69.5f, pos.y - 8));
    sfRenderWindow_drawSprite(Win.self, select, NULL);
    sfSprite_destroy(select);
    functions(butt);
    Setting.hover = true;
    return (sfColor_fromRGB(243, 199, 77));
}

static void draw_back(v2f_t pos, float scal)
{
    sfSprite *bac = sfSprite_create();

    sfSprite_setTexture(bac, Assets.ui[UI_BOX]->self, false);
    sfSprite_setOrigin(bac, V2F(53.0f, 63.0f));
    sfSprite_setScale(bac, V2F(1.5f, 1.0f));
    sfSprite_setPosition(bac, PX_TO_MAPF(V2F(pos.x, pos.y + scal * 2.25)));
    sfRenderWindow_drawSprite(Win.self, bac, false);
    sfSprite_destroy(bac);
}

static void draw_butt(v2f_t pos, float scal)
{
    draw_back(pos, scal);
    draw_text_center("Resume", pos, 0.45f, get_color(PX_TO_MAPF(pos), 1));
    draw_text_center("Axopedia", V2F(pos.x, pos.y + scal), 0.45f,
        get_color(PX_TO_MAPF(V2F(pos.x, pos.y + scal)), 2));
    draw_text_center("Settings", V2F(pos.x, pos.y + scal * 2), 0.45f,
        get_color(PX_TO_MAPF(V2F(pos.x, pos.y + scal * 2)), 3));
    if (Engine.level == 0)
        draw_text_center("Quit", V2F(pos.x, pos.y + scal * 3), 0.45f,
            get_color(PX_TO_MAPF(V2F(pos.x, pos.y + scal * 3)), 4));
    else {
        draw_text_center("Restart", V2F(pos.x, pos.y + scal * 3), 0.45f,
            get_color(PX_TO_MAPF(V2F(pos.x, pos.y + scal * 3)), 5));
        draw_text_center("Abandon", V2F(pos.x, pos.y + scal * 4), 0.45f,
            get_color(PX_TO_MAPF(V2F(pos.x, pos.y + scal * 4)), 6));
    }
    draw_cursor();
}

void pause_loop(void)
{
    sfEvent evt;
    float scal = 3.0f * 16.0f * Win.width / Win.viewWidth * 0.45f;
    v2f_t pos = {Win.width / 2.0f, Win.height / 2};

    while (sfRenderWindow_pollEvent(Win.self, &evt)) {
        if (evt.type == sfEvtClosed)
            sfRenderWindow_close(Win.self);
        CLICK_REL = click_rel(evt);
        if (evt.type == sfEvtKeyReleased &&
            evt.key.code == Setting.pause.code)
            Engine.scene = SCENE_GAME;
    }
    Setting.last_scene = SCENE_PAUSE;
    draw();
    draw_shadow();
    Setting.hover = false;
    draw_butt(pos, scal);
}
