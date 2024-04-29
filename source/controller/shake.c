/*
** EPITECH PROJECT, 2024
** B-MUL-200-LYN-2-1-myrpg-mallory.scotton
** File description:
** shake
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "rpg.h"

///////////////////////////////////////////////////////////////////////////////
void shake(float intensity, float duration)
{
    Player.shaking = true;
    Player.shakeDuration = (ulong_t)(duration * 1e3);
    Player.shakeIntensity = intensity / 100.0f;
    Player.shakeStarting = Time.currentTime;
    Player.shakeOffset = V2F1(0.0f);
    Player.viewCenter = sfView_getCenter(Win.view);
}

///////////////////////////////////////////////////////////////////////////////
void update_shaking(void)
{
    float elapsed = (Time.currentTime - Player.shakeStarting) / 1000.0f;
    float shakeDuration = (float)Player.shakeDuration / 1000.0f;
    float shakeFactor = 0.0f;

    if (!Player.shaking)
        return;
    if (elapsed < shakeDuration) {
        shakeFactor = 1.0f - elapsed / shakeDuration;
        Player.shakeOffset.x = (rand() % 200 - 100) * Player.shakeIntensity *
            shakeFactor;
        Player.shakeOffset.y = (rand() % 200 - 100) * Player.shakeIntensity *
            shakeFactor;
    } else {
        Player.shakeOffset = V2F1(0.0f);
        Player.shaking = false;
    }
    sfView_setCenter(Win.view, add2f(Player.viewCenter, Player.shakeOffset));
    sfRenderWindow_setView(Win.self, Win.view);
}
