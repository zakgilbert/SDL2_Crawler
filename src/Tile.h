#ifndef TILE_H
#define TILE_H
typedef struct _Tile {
    void (*destroy)(struct _Tile* this);                    /* Free Allocated Memory */
    void (*print)(struct _Tile* this, const char* message); /* Print address of Tile type with message */
    SDL_Rect* rect;
    int index;
    int x_origin, y_origin;
} Tile;
Tile* CREATE_TILE();

#endif /* TILE_H */
