#ifndef TERRAIN_H
#define TERRAIN_H

typedef SDL_Renderer Rend;
typedef struct _Tile Tile;

typedef struct _Terrain {
    void (*destroy)(struct _Terrain* this);                    /* Free Allocated Memory */
    void (*print)(struct _Terrain* this, const char* message); /* Print address of Terrain type with message */
    char* (*render)(void* obj, Rend* renderer);
    char* (*logic)(void* obj);
    SDL_Texture* tex;
    SDL_Texture* tex_t;
    SDL_Rect rect;
    SDL_Rect** rects;
    SDL_Rect* current_tile;
    SDL_Rect map_rect;
    int* map;

    char *path, *key;
    int x, y, w, h, tile_w, tile_h, rows, cols;
    int num_tiles, num_tiles_col, num_tiles_row, num_frames;

} Terrain;
Terrain* CREATE_TERRAIN(char* path, char* key, Rend* renderer, int x, int y, int w, int h, int tile_w, int tile_h, int rows, int cols);

#endif /* TERRAIN_H */
