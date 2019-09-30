#ifndef ENEMY_H
#define ENEMY_H

typedef struct _Sprite Sprite;

typedef struct _Enemy {
    void (*destroy)(struct _Enemy* this);                             /* Free Allocated Memory */
    void (*print)(struct _Enemy* this, const char* message);          /* Print address of Enemy type with message */
    char* (*render)(void* obj, SDL_Renderer* renderer);               /* Render function */
    char* (*logic)(void* obj);                                        /* Logic Function */
    void (*add_sprite)(struct _Enemy* this, Sprite* sprite, int key); /* Add a sprite sheet to class */

    Sprite** sprites;     /* List of Sprite Sheets */
    SDL_Texture* texture; /* Texture to be rendered */
    SDL_Rect * col_rect;

    int cur_sprite;
    int num_sprite;
    int moving;
    int *x, *y;

    char* key;
} Enemy;
Enemy* CREATE_ENEMY(char* key, int num_sprite, int* x, int* y);

#endif /* ENEMY_H */
