
/**
*  Terrain.c
*/
#include <SDL2/SDL.h>
#include "Tile.h"
#include "Terrain.h"
#include "Graphics.h"
#include "Header.h"

static int rand_range(int low, int up)
{
    return (rand() % (up - low + 1)) + low;
}
static void set_sprite_cords(Terrain* this)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < this->num_frames; i++) {
        this->rects[i] = malloc(sizeof(struct SDL_Rect));
        if (x >= (this->rect.w * this->cols)) {
            y += this->rect.h;
            x = 0;
        }
        this->rects[i]->x = x;
        this->rects[i]->y = y;
        this->rects[i]->w = this->rect.w;
        this->rects[i]->h = this->rect.h;
        x += this->rect.w;
    }
    for (int i = 0; i < this->num_tiles; i++) {
        this->map[i] = rand_range(0, this->num_frames - 1);
    }
}

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
    SDL_RenderCopy(renderer, this->tex_t, NULL, &this->map_rect);
    return this->key;
}

static char* _logic(void* obj)
{
    Terrain* this    = (Terrain*)obj;
    this->map_rect.x = X;
    this->map_rect.y = Y;
    return this->key;
}
static void create_map(Terrain* this, Rend* renderer)
{
    int i;
    int num_ti;
    int col;
    int row;
    int k_col;
    int k_row;
    int k_rand;
    int *x, *y, w, h, half_w, half_h;
    int stag = 1;

    i            = 0;
    num_ti       = this->num_tiles;
    col          = this->num_tiles_col;
    row          = this->num_tiles_row;
    w            = this->tile_w;
    h            = this->tile_h;
    half_w       = w / 2;
    half_h       = h / 2;
    this->rect.x = 0 - half_w;
    this->rect.y = 0 - half_h;
    x            = &this->rect.x;
    y            = &this->rect.y;
    k_col        = 0;
    k_row        = 0;

    SDL_SetRenderTarget(renderer, this->tex_t);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (; i < num_ti; i++) {
        if (k_col >= col) {
            k_col = 0;
            k_row++;
            if (stag) {
                *x = 0 - half_w;
            } else {
                *x = 0;
            }
            *y += half_h;
            stag = !stag;
        } else {
            k_col++;
            *x += w;
        }
        SDL_RenderCopy(renderer, this->tex, this->rects[this->map[i]], &this->rect);
    }
    SDL_SetRenderTarget(renderer, NULL);
}
Terrain* CREATE_TERRAIN(char* path, char* key, Rend* renderer, int x, int y, int w, int h, int tile_w, int tile_h, int rows, int cols)
{
    Terrain* this = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->print   = _print;
    this->render  = _render;
    this->logic   = _logic;

    this->x          = x;
    this->y          = y;
    this->w          = w;
    this->h          = h;
    this->map_rect.x = x;
    this->map_rect.y = y;
    this->map_rect.w = w;
    this->map_rect.h = h;

    this->tile_w        = tile_w;
    this->tile_h        = tile_h;
    this->rows          = rows;
    this->cols          = cols;
    this->num_frames    = rows * cols;
    this->num_tiles_col = w / tile_w;
    this->num_tiles_row = h / tile_h;
    this->num_tiles     = this->num_tiles_col * this->num_tiles_row;
    this->path          = path;
    this->key           = key;

    this->tex    = create_texture(renderer, path, &this->rect);
    this->tex_t  = NULL;
    this->rect.w = tile_w;
    this->rect.h = tile_h;
    // mTexture = SDL_CreateTexture( gRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height );
    this->tex_t = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    this->map   = malloc(sizeof(int) * this->num_tiles);
    this->rects = malloc(sizeof(struct SDL_Rect*) * this->num_frames);
    set_sprite_cords(this);
    create_map(this, renderer);
    if (PRINT)
        this->print(this, "Allocating");

    return this;
}
