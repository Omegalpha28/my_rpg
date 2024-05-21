/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** interfaces
*/

#ifndef INTERFACES_H_
    #define INTERFACES_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Loop for playing fullscreened video
///
///////////////////////////////////////////////////////////////////////////////
void video_loop(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Loop for the main menu
///
///////////////////////////////////////////////////////////////////////////////
void menu_loop(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Loop for the settings
///
///////////////////////////////////////////////////////////////////////////////
void settings_loop(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Load and Play a video
///
/// \param path         The path of the video
/// \param soundName    The audio of the video
///
///////////////////////////////////////////////////////////////////////////////
void load_video(cstring_t path, cstring_t soundName);

///////////////////////////////////////////////////////////////////////////////
/// \brief Draw the background for the menu and settings
///
///////////////////////////////////////////////////////////////////////////////
void draw_menu_background(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Draw the cursor for the main menu and the settings
///
///////////////////////////////////////////////////////////////////////////////
void draw_cursor(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
///////////////////////////////////////////////////////////////////////////////
void saves_loop(void);

void inventory_loop(void);
void pause_loop(void);
void draw_shadow(void);
bool_t key_rel(sfEvent evt);
bool_t click_rel(sfEvent evt);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param str          TODO:
/// \param pos          TODO:
/// \param scale        TODO:
/// \param color        TODO:
///
///////////////////////////////////////////////////////////////////////////////
void draw_text_right(cstring_t str, v2f_t pos, float scale, sfColor color);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param str          TODO:
/// \param pos          TODO:
/// \param scale        TODO:
/// \param color        TODO:
///
///////////////////////////////////////////////////////////////////////////////
void draw_text_center(cstring_t str, v2f_t pos, float scale, sfColor color);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param pos          TODO:
/// \param str          TODO:
/// \param scale        TODO:
/// \param center       TODO:
///
///////////////////////////////////////////////////////////////////////////////
sfColor colums(v2f_t pos, cstring_t str, float scale, int center);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
///////////////////////////////////////////////////////////////////////////////
void draw_keybinds(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
///////////////////////////////////////////////////////////////////////////////
void draw_audio(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
///////////////////////////////////////////////////////////////////////////////
void draw_video(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param pos          TODO:
/// \param on           TODO:
///
/// \return TODO:
///
///////////////////////////////////////////////////////////////////////////////
sfColor on_off(v2f_t pos, bool_t *on);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param pos          TODO:
///
/// \return TODO:
///
///////////////////////////////////////////////////////////////////////////////
sfColor resolu(v2f_t pos);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
///////////////////////////////////////////////////////////////////////////////
void draw_levitating_logo(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Print all the debug information on the screen
///
///////////////////////////////////////////////////////////////////////////////
void print_debug_information(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
/// \param axo_name     TODO:
/// \param id           TODO:
///
///////////////////////////////////////////////////////////////////////////////
void change_player(cstring_t axo_name, uint_t id);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
///////////////////////////////////////////////////////////////////////////////
void draw_health(void);

#endif /* !INTERFACES_H_ */
