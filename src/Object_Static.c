
/**
 *  Object_Static.c
 */

#include <SDL2/SDL.h>
#include "Graphics.h"

#include "Header.h"
#include "Object_Static.h"

static char* tag = "Object_Static";

static void _destroy(Object_Static* this)
{
    if (NULL != this) {
        if (PRINT)
            printf("%p %s\n", (void*)this, tag);
        free(this);
    }
}

Object_Static* CREATE_OBJECT_STATIC(
    Rend* renderer, char* path, int x, int y, int w, int h)
{
    Object_Static* this = malloc(sizeof(*this));
    this->destroy       = _destroy;

    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;

    this->texture = create_texture(renderer, path, &this->rect);
    if (PRINT)
        printf("%p %s\n", (void*)this, tag);

    return this;
}
