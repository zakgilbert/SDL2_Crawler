#ifndef ATLAS_H
#define ATLAS_H

typedef struct _Alpha_Node Alpha_Node;

/**
 * Hash Alpha_Nodes
 */
typedef struct _Atlas {
    void (*insert)(struct _Atlas* this, const char* key, SDL_Renderer* renderer, const char* path); /* Insert into hashtable */
    void (*destroy)(struct _Atlas* this); /* Free Allocated memory */
    Alpha_Node* (*search)(struct _Atlas* this, const char* key); /* Find element of key */
    void (*map)(struct _Atlas* this, SDL_Renderer* renderer); /* Add alphabet to table */
    void (*render)(Alpha_Node* node, SDL_Renderer* renderer); /* render function for */

    Alpha_Node** letters; /* Array of letter nodes */
    int size; /* Size of letters */
    int count; /* Number of nodes hashed to array */

} Atlas;
Atlas* CREATE_ATLAS();
#endif /* ATLAS_H */
