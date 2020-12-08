#ifndef OBJECT_STATIC_H
#define OBJECT_STATIC_H

typedef SDL_Renderer Rend;
typedef struct _Object_Static {
    void (*destroy)(struct _Object_Static* this);                    /* Free Allocated Memory */
    void (*print)(struct _Object_Static* this, const char* message); /* Print address of Terrain type with message */
    SDL_Texture* texture;
    SDL_Rect rect;
} Object_Static;
Object_Static* CREATE_OBJECT_STATIC(Rend* renderer, char* path, int x, int y, int w, int h);

#endif /* OBJECT_STATIC_H */
