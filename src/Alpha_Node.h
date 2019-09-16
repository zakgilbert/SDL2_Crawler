#ifndef ALPHA_NODE_H
#define ALPHA_NODE_H

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Rect SDL_Rect;

/**
 * Encapsulate data for font atlas 
 */
typedef struct _Alpha_Node {
    void (*destroy)(struct _Alpha_Node* this); /* Free allocated memory */

    SDL_Texture* texture; /* Letter texture */
    SDL_Rect rect; /* Letter rectangle */
    char* key; /* Node key */
} Alpha_Node;
Alpha_Node* CREATE_ALPHA_NODE();

#endif /* ALPHA_NODE_H */
