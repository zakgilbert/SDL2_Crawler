
/**
*  Alpha_Node.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Alpha_Node.h"
#include "Window_and_Renderer.h"
#include "Header.h"

static void _destroy(Alpha_Node *this)
{
    if (NULL != this)
    {
        if (PRINT)
            printf("Destroy: %p\n", this);
        free(this);
    }
}

Alpha_Node *CREATE_ALPHA_NODE(char *key,  char *path, SDL_Renderer *renderer)
{
    Alpha_Node *this = malloc(sizeof(*this));
    if (PRINT)
        printf("Create: %p\n", this);
    this->destroy = _destroy;

    this->texture = create_texture(renderer, path, &this->rect);
    this->key = key;

    return this;
}
