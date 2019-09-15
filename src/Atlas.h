#ifndef ATLAS_H
#define ATLAS_H

typedef struct _Alpha_Node Alpha_Node;

typedef struct _Atlas
{
    void (*destroy)(struct _Atlas *this);
    void (*insert)(struct _Atlas *this, const char *key, SDL_Renderer *renderer, const char *path);
    Alpha_Node *(*search)(struct _Atlas *this, const char *key);
    void (*map)(struct _Atlas *this, SDL_Renderer *renderer);
    void (*render)(Alpha_Node *node, SDL_Renderer *renderer);
    Alpha_Node **letters;
    int size;
    int count;

} Atlas;
Atlas *CREATE_ATLAS();
#endif /* ATLAS_H */
