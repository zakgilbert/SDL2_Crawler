
/************************
	 *  Sprite_Node.c
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Sprite_Node.h"
#include "Window_and_Renderer.h"

static void _destroy(Sprite_Node *this)
{
    if (NULL != this)
        free(this);
}

static Logic_Node *_render(void *obj, SDL_Renderer *renderer)
{
    Sprite_Node *this = (Sprite_Node *)obj;
    SDL_RenderCopy(renderer, this->text, )
}

Sprite_Node *CREATE_SPRITE_NODE(SDL_Rect *)
{
    Sprite_Node *this = malloc(sizeof(*this));
    this->destroy = _destroy;
    return this;
}
