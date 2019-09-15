#ifndef SPRITE_H
#define SPRITE_H
typedef struct _Sprite
{
    void (*destroy)(struct _Sprite *this);
    void (*print)(struct _Sprite *this);
    void (*render)(void *obj, SDL_Renderer *renderer);
    void (*logic)(void *obj);
    SDL_Rect **rects;
    SDL_Rect rect;
    SDL_Rect *frame;
    int num_frames;
    SDL_Texture *texture;
    int type, cols, rows, row_index, col_index;
    struct _Sprite *walk;
    struct _Sprite *temp;

} Sprite;
Sprite *CREATE_SPRITE(SDL_Renderer *renderer, char *path, int rows, int cols, int w, int h, int type);

#endif /* SPRITE_H */
