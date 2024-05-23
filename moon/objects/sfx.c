/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** sfx
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
sfSound *sfx(sfx_list_t n)
{
    sfSound *sound = sfSound_create();
    sfx_t *sfx = Assets.sfx[n];

    if (sound == NULL || sfx == NULL)
        return (NULL);
    sfSound_setVolume(sound, (Setting.master * (Setting.sound / 100.0f)));
    sfSound_setBuffer(sound, sfx->sounds[rand() % sfx->soundCount]);
    Pool.soundCount++;
    Pool.sounds = REALLOC(Pool.sounds, sizeof(sfSound *), Pool.soundCount);
    Pool.sounds[Pool.soundCount - 1] = sound;
    sfSound_play(sound);
    return (sound);
}

///////////////////////////////////////////////////////////////////////////////
void remove_sfx(sfSound *sd)
{
    sfSound **tmp = NULL;
    uint_t j = 0U;

    if (sd == NULL)
        return;
    tmp = malloc(sizeof(sfSound *) * (Pool.soundCount - 1));
    for (uint_t i = 0; i < Pool.soundCount; i++) {
        if (Pool.sounds[i] == sd)
            continue;
        tmp[j] = Pool.sounds[i];
        j++;
    }
    Pool.soundCount--;
    FREE(Pool.sounds);
    Pool.sounds = tmp;
    sfSound_destroy(sd);
}

///////////////////////////////////////////////////////////////////////////////
void remove_completed_sound(void)
{
    for (uint_t i = 0; i < Pool.soundCount; i++) {
        if (sfSound_getStatus(Pool.sounds[i]) == sfPlaying)
            continue;
        remove_sfx(Pool.sounds[i]);
        i--;
    }
}
