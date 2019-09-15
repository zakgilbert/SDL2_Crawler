#ifndef RENDER_NODE_H
#define RENDER_NODE_H

typedef struct SDL_Renderer SDL_Renderer;
typedef void render_function(void *obj, SDL_Renderer *renderer);
/**
 * A node type to be inserted into a hashtable using Hash.h.
 * Should (int data) need to be changed to a different data type lines 20 and 22 will need to be changed in Render_Node.h, as well as lines 30, and 33 in Render_Node.c.
 */
typedef struct _Render_Node
{
    /**
     * Deallocates all memory that of which was allocated at the Render_Nodes creation.
     */
    void (*destroy)(struct _Render_Node *this);

    /**
     * prints Render_Nodes data, key, address.
     */
    void (*print)(struct _Render_Node *this, int i);
    void *obj;
    char *key;
    render_function(*funct);
    int index;
} Render_Node;
Render_Node *CREATE_RENDER_NODE(char *key, void *obj, render_function funct);

#endif /* RENDER_NODE_H */
