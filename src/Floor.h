
#ifndef JRPG_FLOOR_H
#define JRPG_FLOOR_H

/**
 * Encapsulate a SDL Texture that resembles the ground in SDL2_Crawler,
 * see map and forest in main.c
*/
typedef struct _Floor {
    void (*destroy)(struct _Floor*);                    /* Free Allocated Memory */
    char* (*render)(void* obj, SDL_Renderer* renderer); /* Render function */
    char* (*logic)(void* obj);                          /* Logic function */

    SDL_Texture* texture; /* SDL Texture */
    SDL_Rect rect;        /* SDL Rectangle */

    char* path;
} Floor;

Floor* CREATE_FLOOR(int x, int y, int w, int h, SDL_Renderer* renderer, char* path);

#endif
