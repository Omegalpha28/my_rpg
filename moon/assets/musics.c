/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** musics
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static bool_t add_music(string_t path)
{
    music_t *music = (music_t *)malloc(sizeof(music_t));
    warray_t split = my_strsplit(path, '/');
    ulong_t last = my_walen(split) - 1;
    ulong_t len = my_strlen(split[last]);

    music->self = sfMusic_createFromFile(path);
    music->name = music->self ? my_strndup(split[last], (len - 4)) : NULL;
    my_watroy(split);
    if (!music->self) {
        FREE(music);
        return (my_error(ERR_LOAD_MUSIC));
    }
    sfMusic_setLoop(music->self, true);
    Assets.musicCount++;
    Assets.musics = REALLOC(Assets.musics, sizeof(music_t *),
        Assets.musicCount);
    Assets.musics[Assets.musicCount - 1] = music;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
bool_t init_assets_musics(void)
{
    warray_t content = my_dircontent(DIR_MUSICS);
    bool_t success = true;

    if (content == NULL)
        return (my_error(ERR_FD_MUSICS));
    for (uint_t i = 0; success && content[i]; i++) {
        if (my_isdir(content[i]) || !my_extname(content[i]) ||
            !CMP(my_extname(content[i]), EXT_MUSICS))
            continue;
        success = add_music(content[i]);
    }
    my_watroy(content);
    return (success);
}

void set_asset_music_status(sfSoundStatus status)
{
    for (uint_t i = 0; i < Assets.musicCount; i++) {
        if (sfMusic_getStatus(Assets.musics[i]->self) == status &&
            status == sfPaused)
            sfMusic_play(find_music(Assets.musics[i]->name));
        if (sfMusic_getStatus(Assets.musics[i]->self) == status &&
            status == sfPlaying)
            sfMusic_pause(find_music(Assets.musics[i]->name));
    }
}

///////////////////////////////////////////////////////////////////////////////
void destroy_assets_musics(void)
{
    for (uint_t i = 0; i < Assets.musicCount; i++) {
        if (Assets.musics[i] == NULL)
            continue;
        FREE(Assets.musics[i]->name);
        if (Assets.musics[i]->self)
            sfMusic_destroy(Assets.musics[i]->self);
        FREE(Assets.musics[i]);
    }
    FREE(Assets.musics);
    Assets.musics = NULL;
    Assets.musicCount = 0;
}

///////////////////////////////////////////////////////////////////////////////
sfMusic *find_music(cstring_t name)
{
    for (uint_t i = 0; i < Assets.musicCount; i++)
        if (CMP(name, Assets.musics[i]->name))
            return (Assets.musics[i]->self);
    return (NULL);
}
