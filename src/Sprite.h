#ifndef SPRITE_H
#define SPRITE_H

/**
 * Encapsulate data for rendering textures from a sprite sheet 
 */
typedef struct _Sprite {
    void (*destroy)(struct _Sprite* this);             /* Free allocated memory */
    void (*print)(struct _Sprite* this);               /* Print Sprite data */
    void (*render)(void* obj, SDL_Renderer* renderer); /* Render Sprite texture */
    void (*logic)(void* obj);                          /* Execute Sprite game logic */

    SDL_Rect** rects;     /* Array of SDL Rentangle pointers for each frame in the sprite */
    SDL_Rect rect;        /* SDL Rectangle for entire Sprite sheet texture */
    SDL_Rect* frame;      /* SDL Rectangle for the frame to be rendered */
    SDL_Texture* texture; /* SDL Texture to be rendered */
    int num_frames;       /* THe number of frames */
    int state;            /* The type of sprite */
    int type;
    int cols;      /* Number of columns */
    int rows;      /* Number of rows */
    int row_index; /* */
    int col_index; /* */
    int action_started;
    int x_origin;
    int y_origin;
    int moving;
    int time_begin;
    int time_end;

} Sprite;
Sprite* CREATE_SPRITE(SDL_Renderer* renderer, char* path, int rows, int cols, int x, int y, int w, int h, int state, int type);

#endif /* SPRITE_H */