
/**
*  Terrain.c
*/
#include <SDL2/SDL.h>
#include "Tile.h"
#include "Terrain.h"
#include "Graphics.h"
#include "Header.h"

static void _destroy(Terrain* this)
{
    if (NULL != this) {
        if (PRINT)
            this->print(this, "Freeing");
        free(this);
    }
}

static void _print(Terrain* this, const char* message)
{
    printf("Terrain: %p  %s\n", this, message);
}

static char* _render(void* obj, Rend* renderer)
{
    Terrain* this = (Terrain*)obj;
    SDL_RenderCopy(renderer, this->tex, NULL, &this->rect);
    return this->key;
}

static char* _logic(void* obj)
{
    Terrain* this = (Terrain*)obj;
    this->rect.x  = X;
    this->rect.y  = Y;
    return this->key;
}

Terrain* CREATE_TERRAIN(char* path, char* key, Rend* renderer, int x, int y, int w, int h, int tile_w, int tile_h, int rows, int cols)
{
    Terrain* this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->print   = _print;
    this->render  = _render;
    this->logic   = _logic;

    this->x         = x;
    this->y         = y;
    this->w         = w;
    this->h         = h;
    this->tile_w    = tile_w;
    this->tile_h    = tile_h;
    this->rows      = rows;
    this->cols      = cols;
    this->num_tiles = rows * cols;
    this->path      = path;
    this->key       = key;

    this->tex = create_texture(renderer, path, &this->rect);
    if (PRINT)
        this->print(this, "Allocating");

    return this;
}
