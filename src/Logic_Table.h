#ifndef LOGIC_TABLE_H
#define LOGIC_TABLE_H

typedef struct SDL_Renderer SDL_Renderer;
typedef struct _Logic_Node Logic_Node;
typedef void render_function(void *obj, SDL_Renderer *renderer);

/** 
 * Hash Logic Nodes 
 */
typedef struct _Logic_Table
{
    void (*destroy)(struct _Logic_Table *this);                  /* Free allocated memory */
    Logic_Node *(*search)(struct _Logic_Table *this, char *key); /* Perform a hash search for the given key */
    void (*print_table)(struct _Logic_Table *this);              /* Print Hashtable */
    void (*grow)(struct _Logic_Table *this);                     /* Double the size of hashtable */
    void (*insert)(struct _Logic_Table *this, Logic_Node *item); /* Insert a new node into hashtable. */
    void (*delete)(struct _Logic_Table *this, char *key);        /* Delete node of key */

    Logic_Node **table; /* Array of Logic Node Pointers */
    int size;           /* size of table */
    int count;          /* number of nodes hash into table */

} Logic_Table;

Logic_Table *CREATE_LOGIC_TABLE(int size);

#endif /* LOGIC_TABLE_H */
