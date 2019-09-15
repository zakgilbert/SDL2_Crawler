
#ifndef JRPG_FLOOR_H
#define JRPG_FLOOR_H

typedef struct _Floor
{
    void (*destroy)(struct _Floor *);
    void (*render)(void * obj, SDL_Renderer * renderer);
    void (*logic)(void *obj);
    SDL_Texture *texture;
    SDL_Rect rect;
    int tex_width;
    int tex_height;

} Floor;

Floor *CREATE_FLOOR(int x, int y, int w, int h, SDL_Renderer *renderer, const char *path);

#endif
