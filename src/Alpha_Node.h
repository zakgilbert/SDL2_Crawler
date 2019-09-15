#ifndef ALPHA_NODE_H
#define ALPHA_NODE_H

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Rect SDL_Rect;

typedef struct _Alpha_Node
{
    void (*destroy)(struct _Alpha_Node *this);
    SDL_Texture *texture;
    SDL_Rect rect;
    char *key;
} Alpha_Node;
Alpha_Node *CREATE_ALPHA_NODE();

#endif /* ALPHA_NODE_H */
