/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** window
*/

#ifndef WINDOW_H_
    #define WINDOW_H_

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
    #include "moon.h"

///////////////////////////////////////////////////////////////////////////////
//
// PARAMETERS
//
///////////////////////////////////////////////////////////////////////////////

    /** Mode for the window: 'fullscreen', 'borderless', 'windowed'.         */
    #define WIN_FULLSCREEN (sfFullscreen)
    #define WIN_BORDERLESS (sfNone)
    #define WIN_WINDOWED (sfTitlebar | sfClose)

///////////////////////////////////////////////////////////////////////////////
//
// CONFIGURATION
//
///////////////////////////////////////////////////////////////////////////////

    /** Default window size                                                  */
    #define DEFAULT_WIDTH 1920
    #define DEFAULT_HEIGHT 1080
    /** View settings                                                        */
    #define DEFAULT_VIEW_WIDTH 512
    #define DEFAULT_VIEW_HEIGHT 288
    /** Window color bits                                                    */
    #define DEFAULT_BITS 32
    /** Framerate limit                                                      */
    #define DEFAULT_FPS 60
    /** Window default mode: 'fullscreen'                                    */
    #define DEFAULT_MODE WIN_FULLSCREEN
    /** Window configuration                                                 */
    #define DEFAULT_TITLE "AK-XOLOTL"
    #define DEFAULT_ICON "game-icon.png"

///////////////////////////////////////////////////////////////////////////////
//
// STRUCTURES
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// \brief Time instance for the game
///
/// \param deltaTime    Delta time spend between the render of two frames
/// \param currentTime  The current time of the process, start at 0
/// \param clock        The clock element to keep track of the time
///
///////////////////////////////////////////////////////////////////////////////
extern struct window_time_s {
    double deltaTime;
    u32 currentTime;
    sfClock *clock;
} Time;

///////////////////////////////////////////////////////////////////////////////
/// \brief Window references structure, handle mode/parameters and view
///
/// \param view         The 'camera' of the game
/// \param self         Reference to the window element
/// \param width        The width of the window 'DEFAULT_WIDTH' by default
/// \param height       The height of the window 'DEFAULT_HEIGHT' by default
/// \param mode         The window mode's: 'fullscreen', 'borderless',
///                     'windowed'
///
///////////////////////////////////////////////////////////////////////////////
extern struct window_reference_s {
    sfView *view;
    sfRenderWindow *self;
    uint width;
    uint height;
    int mode;
} Win;

///////////////////////////////////////////////////////////////////////////////
//
// FUNCTIONS
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// \brief Create a new window width the wanted parameters
///
/// \param width        The width of the window (if 0, default value)
/// \param height       The height of the window (if 0, default value)
/// \param mode         Window mode: 'fullscreen', 'borderless', 'windowed'
///
/// \return Boolean, true if the creation was successful, false otherwise
///
///////////////////////////////////////////////////////////////////////////////
bool create_window(uint width, uint height, int mode);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy the window and view from the Win structure
///
///////////////////////////////////////////////////////////////////////////////
void destroy_window(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Initialize the global Time variable, and all the components linked
///
/// \return The status of the operation, if the operation fail, stop the game
/// engine.
///
///////////////////////////////////////////////////////////////////////////////
bool init_time(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Update the Time variable
///
/// This function need to be executed at the start of each frame for the
/// calculation of the deltaTime.
///
/// \return The status of the operation, if the operation fail, it means that
/// the initialization failed, and need to leave the engine.
///
///////////////////////////////////////////////////////////////////////////////
bool update_time(void);

///////////////////////////////////////////////////////////////////////////////
/// \brief Destroy the variable and clean the used ressources
///
/// This function will free the memory and destroy the clock to clean
/// the used ressources.
///
///////////////////////////////////////////////////////////////////////////////
void destroy_time(void);

#endif /* !WINDOW_H_ */
