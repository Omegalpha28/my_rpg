/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** images
*/

///////////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////////
#include "moon.h"

///////////////////////////////////////////////////////////////////////////////
static image_t *image_load(cstring_t filepath, v2u_t grid, image_t *img)
{
    img->self = sfTexture_createFromFile(filepath, NULL);
    if (img->self == NULL) {
        free(img);
        return (NULL);
    }
    img->size = sfTexture_getSize(img->self);
    img->mask = (recti_t){0, 0, img->size.x / grid.x, img->size.y / grid.y};
    return (img);
}

///////////////////////////////////////////////////////////////////////////////
image_t *add_image(cstring_t filepath, bool_t load, v2u_t grid, cstring_t name)
{
    image_t *img = (filepath) ? (image_t *)malloc(sizeof(image_t)) : NULL;

    if (img == NULL)
        return (NULL);
    Assets.imageCount++;
    Assets.images = my_orealloc(Assets.images, sizeof(image_t *) *
        (Assets.imageCount - 1), sizeof(image_t *) * (Assets.imageCount));
    Assets.images[Assets.imageCount - 1] = img;
    img->grid = grid;
    img->size = (v2u_t){0, 0};
    img->filepath = my_strdup(filepath);
    img->name = my_strdup(name);
    if (load == false)
        return (img);
    return (image_load(filepath, grid, img));
}

///////////////////////////////////////////////////////////////////////////////
void load_image(image_t *img)
{
    if (!img || !img->filepath || img->self)
        return;
    img->self = sfTexture_createFromFile(img->filepath, NULL);
    img->size = sfTexture_getSize(img->self);
    img->mask = (recti_t){0, 0, img->size.x / img->grid.x,
        img->size.y / img->grid.y};
}

///////////////////////////////////////////////////////////////////////////////
void unload_image(image_t *img)
{
    if (!img || !img->self)
        return;
    sfTexture_destroy(img->self);
    img->self = NULL;
}
