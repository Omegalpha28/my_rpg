/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** levels
*/

#ifndef LEVELS_H_
    #define LEVELS_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
/// \brief Clear the entity remove queue
///
///////////////////////////////////////////////////////////////////////////////
void clear_entity_remove_queue(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
///////////////////////////////////////////////////////////////////////////////
bool_t level_tutorial(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
///////////////////////////////////////////////////////////////////////////////
bool_t level_hub(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief TODO:
///
///////////////////////////////////////////////////////////////////////////////
void switch_level(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Compile and save the current loaded level to the desired filepath
///
/// \param filepath     The file path to save the level
///
/// \return Ture if the level is saved, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t level_save(cstring_t filepath);

///////////////////////////////////////////////////////////////////////////////
/// \brief Load a level into the Editor values
///
/// \param filepath     The file path to load the level
///
/// \return True if the level is loaded, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool_t level_load(cstring_t filepath);

///////////////////////////////////////////////////////////////////////////////
/// \brief Check for the level end
///
///////////////////////////////////////////////////////////////////////////////
void check_level_end(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Stop every musics from the game
///
///////////////////////////////////////////////////////////////////////////////
void end_music(void);

#endif /* !LEVELS_H_ */
