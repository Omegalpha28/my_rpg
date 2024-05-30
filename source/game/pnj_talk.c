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
void draw_next_button(void)
{
    sfSprite *btn = sfSprite_create();
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};

    sfSprite_setTexture(btn, Assets.ui[UI_BUTTONS]->self, false);
    sfSprite_setTextureRect(btn, (recti_t){22, 16, 18, 12});
    draw_text("Pass", PX_TO_MAPF(V2F(Win.width / 2 + scale.x * 120,
        Win.height / 5 * 3.5f + 38.0f * scale.y)),
        FACTORS(V2F1(20.0f)).x * 2.0f, WHITE);
    sfSprite_setScale(btn, V2F1(0.8f));
    sfSprite_setPosition(btn, PX_TO_MAPF(V2F(Win.width / 2 + scale.x * 104,
        Win.height / 5 * 3.5f + 38.0f * scale.y)));
    sfRenderWindow_drawSprite(Win.self, btn, NULL);
    sfSprite_destroy(btn);
}

///////////////////////////////////////////////////////////////////////////////
void switalk(interactable_t *obj)
{
    actor_set_anim(Player.ref, "sit");
    if (obj->data[0] == 8 && Engine.level == 3)
        Setting.talk = TUTO_1;
    if (obj->data[0] == 8 && Engine.level == 4)
        Setting.talk = TUTO_2;
    if (obj->data[0] == 4)
        Setting.talk = MARKET_ITEM;
    if (obj->data[0] == 3)
        Setting.talk = INVENTORY;
    if (obj->data[0] == 2)
        Setting.talk = MARKET_WEAPON;
    if (obj->data[0] == 1)
        Setting.talk = JOURNAL;
}

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
static void draw_tuto1(v2f_t scale)
{
    sfSprite *sign = sfSprite_create();

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
    draw_next_button();
}

///////////////////////////////////////////////////////////////////////////////
static void draw_tuto2(v2f_t scale)
{
    sfSprite *sign = sfSprite_create();

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
    draw_next_button();
}

///////////////////////////////////////////////////////////////////////////////
static void draw_market_weap(v2f_t scale)
{
    sfSprite *sign = sfSprite_create();

    draw_shadow();
    sfSprite_setTexture(sign, Assets.ui[UI_PNJ_MARK_WEAP]->self, false);
    sfSprite_setScale(sign, V2F1(0.75f));
    sfSprite_setOrigin(sign, V2F(49.5f, 102.0f));
    sfSprite_setPosition(sign, PX_TO_MAPF(V2F(Win.width / 4 - scale.x * 16.0f,
        Win.height)));
    sfRenderWindow_drawSprite(Win.self, sign, false);
    sfSprite_destroy(sign);
    draw_text("Junkcat", PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 16,
        Win.height / 5 * 3.5f)), 0.45f, sfWhite);
    draw_text(MARK_IT_LINE1, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 16.0f * scale.y)), 0.35f, sfWhite);
    draw_text(MARK_IT_LINE2, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 24.0f * scale.y)), 0.35f, sfWhite);
    Player.blocked = true;
    draw_next_button();
}

///////////////////////////////////////////////////////////////////////////////
static void draw_market_item(v2f_t scale)
{
    sfSprite *sign = sfSprite_create();

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
    draw_next_button();
}

///////////////////////////////////////////////////////////////////////////////
static void draw_journal(v2f_t scale)
{
    sfSprite *sign = sfSprite_create();

    draw_shadow();
    sfSprite_setTexture(sign, Assets.ui[UI_PNJ_JOURN]->self, false);
    sfSprite_setScale(sign, V2F1(0.75f));
    sfSprite_setOrigin(sign, V2F(81.5f, 134.0f));
    sfSprite_setPosition(sign, PX_TO_MAPF(V2F(Win.width / 4 - scale.x * 16.0f,
        Win.height)));
    sfRenderWindow_drawSprite(Win.self, sign, false);
    sfSprite_destroy(sign);
    draw_text("Blisstaker", PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 16,
        Win.height / 5 * 3.5f)), 0.45f, sfWhite);
    draw_text(JOURN_LINE1, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 16.0f * scale.y)), 0.35f, sfWhite);
    draw_text(JOURN_LINE2, PX_TO_MAPF(V2F(Win.width / 3 + scale.x * 8,
        Win.height / 5 * 3.5f + 24.0f * scale.y)), 0.35f, sfWhite);
    Player.blocked = true;
    draw_next_button();
}

///////////////////////////////////////////////////////////////////////////////
void draw_inv(v2f_t scale)
{
    sfSprite *sign = sfSprite_create();

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
    Player.blocked = true;
    draw_next_button();
}

///////////////////////////////////////////////////////////////////////////////
void pnj_talk(talk_t number_talk)
{
    v2f_t scale = {Win.width / Win.viewWidth, Win.height / Win.viewHeight};

    if (number_talk == TUTO_1)
        draw_tuto1(scale);
    if (number_talk == TUTO_2)
        draw_tuto2(scale);
    if (number_talk == MARKET_WEAPON)
        draw_market_weap(scale);
    if (number_talk == MARKET_ITEM)
        draw_market_item(scale);
    if (number_talk == INVENTORY)
        draw_inv(scale);
    if (number_talk == JOURNAL)
        draw_journal(scale);
}
