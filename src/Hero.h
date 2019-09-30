#ifndef HERO_H
#define HERO_H

typedef struct _Sprite Sprite;

typedef struct _Hero {
    void (*destroy)(struct _Hero* this);                             /* Free Allocated Memory */
    void (*print)(struct _Hero* this, const char* message);          /* Print address of Hero type with message */
    char* (*render)(void* obj, SDL_Renderer* renderer);              /* Render function */
    char* (*logic)(void* obj);                                       /* Logic Function */
    void (*add_sprite)(struct _Hero* this, Sprite* sprite, int key); /* Add a sprite sheet to class */

    Sprite** sprites;     /* List of Sprite Sheets */
    SDL_Texture* texture; /* Texture to be rendered */

    int cur_sprite;
    int num_sprite;
    int moving;
    int *x, *y;

    char* key;
} Hero;
Hero* CREATE_HERO(char* key, int num_sprite);

#endif /* HERO_H */
