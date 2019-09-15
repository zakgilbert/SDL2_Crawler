#ifndef RENDER_NODE_H
#define RENDER_NODE_H

typedef void render_function(void *obj, SDL_Renderer *renderer);

/**
 * Encapsulate data for Render Table
 */
typedef struct _Render_Node
{
    void (*destroy)(struct _Render_Node *this);      /* Free allocated memory */
    void (*print)(struct _Render_Node *this, int i); /* Print node data */
    render_function(*funct);                         /* Pointer to render function */

    void *obj; /* Pointer to object whose render function will be called */
    int index; /* Index the node is stored at */
    char *key; /* Key of node */
} Render_Node;
Render_Node *CREATE_RENDER_NODE(char *key, void *obj, render_function funct);

#endif /* RENDER_NODE_H */
