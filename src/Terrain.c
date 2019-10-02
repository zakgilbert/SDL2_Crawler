
/**
*  Terrain.c
*/
#include <SDL2/SDL.h>
#include "Tile.h"
#include "Terrain.h"
#include "Graphics.h"
#include "Header.h"

/**
 * Generate random number between this and that
 */
static int rand_range(int this, int that)
{
    return (rand() % (that - this + 1)) + this;
}

/**
 * Print the map as 2d array
 */
static void print_map(Terrain* this)
{
    printf("Map\n[");
    int col = 0;
    for (int i = 0; i < this->num_tiles; i++) {
        if (col == this->num_tiles_col) {
            col = 0;
            printf("]\n[");
        }
        printf("%d\t", this->map[i]);
        col++;
    }
}

/**
 * Set the coordinates for all rectangles 
 */
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
        this->map[i] = rand_range(0, this->num_frames - 2);
    }
    if (PRINT)
        print_map(this);
}

/**
 * Render map tiles to map texture 
 */
static void create_map(Terrain* this, Rend* renderer)
{
    int i;     /* Index of tiles with respect to the number of tiles */
    int k_col; /* current column index */
    int k_row; /* current row index */
    int stag;  /* decide wether to stagger the row or not */

    i            = 0;
    this->rect.x = 0 - (this->tile_w / 2);
    this->rect.y = 0 - (this->tile_h / 2);
    k_col        = 0;
    k_row        = 0;
    stag         = 0;

    SDL_SetRenderTarget(renderer, this->tex_t);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    for (; i < this->num_tiles; i++) {
        if (k_col > this->num_tiles_col) {
            k_col = 0;
            k_row++;
            if (stag) {
                this->rect.x = 0 - (this->tile_w / 2);
            } else {
                this->rect.x = 0;
            }
            this->rect.y += (this->tile_h / 2);
            stag = !stag;
        } else {
            k_col++;
            this->rect.x += this->tile_w;
        }
        SDL_RenderCopy(renderer, this->tex, this->rects[this->map[i]], &this->rect);
    }
    SDL_SetRenderTarget(renderer, NULL);
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
    this->key           = key;

    this->tex    = create_texture(renderer, path, &this->rect);
    this->tex_t  = NULL;
    this->rect.w = tile_w;
    this->rect.h = tile_h;

    this->tex_t = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    this->map   = malloc(sizeof(int) * this->num_tiles);
    this->rects = malloc(sizeof(struct SDL_Rect*) * this->num_frames);
    set_sprite_cords(this);
    create_map(this, renderer);
    if (PRINT)
        this->print(this, "Allocating");

    return this;
}
