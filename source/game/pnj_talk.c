/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** pnj_talk
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void draw_interact(void)
{
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};
    sfSprite *bac = sfSprite_create();
    string_t butt = conv(Setting.interact.code + 'a');

    sfSprite_setTexture(bac, Assets.ui[UI_KEY]->self, false);
    sfSprite_setOrigin(bac, V2F(5.5f, 6.0f));
    sfSprite_setPosition(bac, PX_TO_MAPF(V2F(Win.width / 2 + 16 * scale.x,
        Win.height / 4 * 3 + 4 * scale.y)));
    sfRenderWindow_drawSprite(Win.self, bac, false);
    sfSprite_destroy(bac);
    draw_text_center(butt, V2F(Win.width / 2 + 16 * scale.x,
        Win.height / 4 * 3), 0.3f, sfColor_fromRGB(124, 137, 138));
    free(butt);
    draw_text_center("Interact", V2F(Win.width / 2 - 16 * scale.x,
        Win.height / 4 * 3), 0.35f, sfWhite);
}

///////////////////////////////////////////////////////////////////////////////
static void draw_tuto1(void)
{
    sfSprite *sign = sfSprite_create();
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};

    draw_shadow();
    sfSprite_setTexture(sign, Assets.ui[UI_PNJ_SIGN]->self, false);
    sfSprite_setScale(sign, V2F1(0.75f));
    sfSprite_setOrigin(sign, V2F(64.5f, 115.0f));
    sfSprite_setPosition(sign, PX_TO_MAPF(V2F(Win.width / 4 - scale.x * 16.0f,
        Win.height)));
    sfRenderWindow_drawSprite(Win.self, sign, false);
    sfSprite_destroy(sign);
    draw_text("Sus Sign", PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 16,
        Win.height / 5 * 3.5f)), 0.45f, sfWhite);
    draw_text(HEAL_LINE1, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 16.0f * scale.y)), 0.35f, sfWhite);
    draw_text(HEAL_LINE2, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 24.0f * scale.y)), 0.35f, sfWhite);
    Player.blocked = true;
}

///////////////////////////////////////////////////////////////////////////////
static void draw_tuto2(void)
{
    sfSprite *sign = sfSprite_create();
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};

    draw_shadow();
    sfSprite_setTexture(sign, Assets.ui[UI_PNJ_SIGN]->self, false);
    sfSprite_setScale(sign, V2F1(0.75f));
    sfSprite_setOrigin(sign, V2F(64.5f, 115.0f));
    sfSprite_setPosition(sign, PX_TO_MAPF(V2F(Win.width / 4 - scale.x * 16.0f,
        Win.height)));
    sfRenderWindow_drawSprite(Win.self, sign, false);
    sfSprite_destroy(sign);
    draw_text("Sus Sign", PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 16,
        Win.height / 5 * 3.5f)), 0.45f, sfWhite);
    draw_text(DASH_LINE1, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 16.0f * scale.y)), 0.35f, sfWhite);
    draw_text(DASH_LINE2, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 24.0f * scale.y)), 0.35f, sfWhite);
    Player.blocked = true;
}

///////////////////////////////////////////////////////////////////////////////
static void draw_market_weap(void)
{
    sfSprite *mark = sfSprite_create();
}

///////////////////////////////////////////////////////////////////////////////
static void draw_market_item(void)
{
    sfSprite *sign = sfSprite_create();
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};

    draw_shadow();
    sfSprite_setTexture(sign, Assets.ui[UI_PNJ_MARK_ITEM]->self, false);
    sfSprite_setScale(sign, V2F1(0.75f));
    sfSprite_setOrigin(sign, V2F(59.0f, 101.0f));
    sfSprite_setPosition(sign, PX_TO_MAPF(V2F(Win.width / 4 - scale.x * 16.0f,
        Win.height)));
    sfRenderWindow_drawSprite(Win.self, sign, false);
    sfSprite_destroy(sign);
    draw_text("Dough", PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 16,
        Win.height / 5 * 3.5f)), 0.45f, sfWhite);
    draw_text(MARK_IT_LINE1, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 16.0f * scale.y)), 0.35f, sfWhite);
    draw_text(MARK_IT_LINE2, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 24.0f * scale.y)), 0.35f, sfWhite);
    Player.blocked = true;
}

///////////////////////////////////////////////////////////////////////////////
static void draw_journal(void)
{
    sfSprite *sign = sfSprite_create();
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};

    draw_shadow();
    sfSprite_setTexture(sign, Assets.ui[UI_PNJ_JOURN]->self, false);
    sfSprite_setScale(sign, V2F1(0.75f));
    sfSprite_setOrigin(sign, V2F(72.0f, 114.0f));
    sfSprite_setPosition(sign, PX_TO_MAPF(V2F(Win.width / 4 - scale.x * 16.0f,
        Win.height)));
    sfRenderWindow_drawSprite(Win.self, sign, false);
    sfSprite_destroy(sign);
    draw_text("Baboon", PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 16,
        Win.height / 5 * 3.5f)), 0.45f, sfWhite);
    draw_text(JOURN_LINE1, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 16.0f * scale.y)), 0.35f, sfWhite);
    draw_text(JOURN_LINE2, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 24.0f * scale.y)), 0.35f, sfWhite);
    Player.blocked = true;
}

///////////////////////////////////////////////////////////////////////////////
void draw_inv(void)
{
    sfSprite *sign = sfSprite_create();
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};

    draw_shadow();
    sfSprite_setTexture(sign, Assets.ui[UI_PNJ_INV]->self, false);
    sfSprite_setScale(sign, V2F1(0.75f));
    sfSprite_setOrigin(sign, V2F(46.0f, 96.0f));
    sfSprite_setPosition(sign, PX_TO_MAPF(V2F(Win.width / 4 - scale.x * 16.0f,
        Win.height)));
    sfRenderWindow_drawSprite(Win.self, sign, false);
    sfSprite_destroy(sign);
    draw_text("Nugget", PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 16,
        Win.height / 5 * 3.5f)), 0.45f, sfWhite);
    draw_text(INV_LINE1, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 16.0f * scale.y)), 0.35f, sfWhite);
    draw_text(INV_LINE2, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 24.0f * scale.y)), 0.35f, sfWhite);
    if (CLICK_REL)
        Engine.scene = SCENE_INVENTORY;
    Player.blocked = true;
}

///////////////////////////////////////////////////////////////////////////////
void pnj_talk(talk_t number_talk)
{
    if (number_talk == TUTO_1)
        draw_tuto1();
    if (number_talk == TUTO_2)
        draw_tuto2();
    if (number_talk == MARKET_WEAPON)
        draw_market_weap();
    if (number_talk == MARKET_ITEM)
        draw_market_item();
    if (number_talk == INVENTORY)
        draw_inv();
    if (number_talk == JOURNAL)
        draw_journal();
}
