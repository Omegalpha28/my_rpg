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
/// \brief Load and Play a video
///
/// \param path         The path of the video
/// \param soundName    The audio of the video
///
///////////////////////////////////////////////////////////////////////////////
void load_video(cstring_t path, cstring_t soundName);

#endif /* !INTERFACES_H_ */