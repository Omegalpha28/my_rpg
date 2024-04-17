/*
** EPITECH PROJECT, 2024
** csfml-engine
** File description:
** time
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
struct window_time_s Time = {
    0.0f, 0, NULL
};

///////////////////////////////////////////////////////////////////////////////
bool_t init_time(void)
{
    Time.clock = sfClock_create();
    if (Time.clock == NULL)
        return (false);
    Time.currentTime = sfTime_asMilliseconds(
        sfClock_getElapsedTime(Time.clock));
    Time.deltaTime = 0.0f;
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
bool_t update_time(void)
{
    sfTime crt;
    v2f_t viewSize = sfView_getSize(Win.view);

    if (Time.clock == NULL)
        return (false);
    Win.viewWidth = viewSize.x;
    Win.viewHeight = viewSize.y;
    crt = sfClock_getElapsedTime(Time.clock);
    Time.deltaTime = sfTime_asMilliseconds(crt) - Time.currentTime;
    Time.currentTime = sfTime_asMilliseconds(crt);
    return (true);
}

///////////////////////////////////////////////////////////////////////////////
void destroy_time(void)
{
    if (Time.clock) {
        sfClock_destroy(Time.clock);
        Time.clock = NULL;
    }
}
