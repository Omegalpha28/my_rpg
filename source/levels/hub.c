/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** hub
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
bool_t level_hub(void)
{
    sfMusic *music = find_music("by-the-campfire");

    if (Engine.level != 0 || !level_load("shared/hub"))
        return (false);
    end_music();
    for (uint_t i = 0; i < Pool.propCount; i++)
        if (CMP(Pool.props[i]->self->name, "torch"))
            effect("firethrower", add2f(Pool.props[i]->position, V2F(0.0f,
                -11.0f)), false);
    sfMusic_setVolume(music, clampf(Setting.master *
        (Setting.music / 100.0f) * 0.75f, 0.0f, 100.0f));
    sfMusic_play(music);
    spawn_interactable(INTERACTABLE_PNJ, V2F(155.0f, -160.0f), 4, NULL);
    spawn_interactable(INTERACTABLE_PNJ, V2F(475.0f, -15.0f), 3, NULL);
    return (true);
}
