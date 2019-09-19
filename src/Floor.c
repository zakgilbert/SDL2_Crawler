#include <SDL2/SDL.h>
#include "Floor.h"
#include "Graphics.h"
#include "Header.h"

static void _destroy(Floor* this)
{
    SDL_DestroyTexture(this->texture);
    if (NULL != this) {
        printf("destroy: %p\n", this);
        free(this);
        this = NULL;
    }
}

static char* _render(void* obj, SDL_Renderer* renderer)
{
    Floor* this = (Floor*)obj;
    SDL_RenderCopy(renderer, this->texture, NULL, &this->rect);

    return this->path;
}

static char* _logic(void* obj)
{
    Floor* this = (Floor*)obj;

    this->rect.x = X;
    this->rect.y = Y;
    return this->path;
}

Floor* CREATE_FLOOR(int x, int y, int w, int h, SDL_Renderer* renderer, char* path)
{
    Floor* this = (Floor*)malloc(sizeof(*this));

    this->destroy = _destroy;
    this->render  = _render;
    this->logic   = _logic;

    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = w;
    this->rect.h = h;
    this->path   = path;

    this->texture = create_texture(renderer, path, &this->rect);

    return this;
}
