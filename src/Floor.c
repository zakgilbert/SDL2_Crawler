
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Header.h"
#include "Floor.h"
#include "Graphics.h"

static void _destroy(Floor *this)
{
    SDL_DestroyTexture(this->texture);
    if (NULL != this)
    {
        printf("destroy: %p\n", this);
        free(this);
        this = NULL;
    }
}

static void _render(void *obj, SDL_Renderer *renderer)
{
    Floor *this = (Floor *)obj;

    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);
}

static void _logic(void *obj)
{
    Floor *this = (Floor *)obj;

    this->rect.x = X;
    this->rect.y = Y;
}

Floor *CREATE_FLOOR(int x, int y, int w, int h, SDL_Renderer *renderer, const char *path)
{
    Floor *this = (Floor *)malloc(sizeof(*this));
    this->destroy = _destroy;
    this->render = _render;
    this->logic = _logic;
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;

    this->texture = create_texture(renderer, path, &this->rect);

    return this;
}
