#ifndef HASH_L_H
#define HASH_L_H

typedef struct SDL_Renderer SDL_Renderer;
typedef struct _Logic_Node Logic_Node;
typedef void render_function(void *obj, SDL_Renderer *renderer);

/**
 * A Hashtable of type logic (a hash table that stores logic nodes)
 * To change the stored data types, edit the nodes fields in Logic_Node.h
 * A hashtable instance can be declared as follows...
 *      Hash_l * hash_table = CREATE_HASH(int size)
 */
typedef struct _Hash_l
{
    void (*destroy)(struct _Hash_l *this);                  /* Frees allocated memory */
    Logic_Node *(*search)(struct _Hash_l *this, char *key); /* Performs a hash search for the given key */
    void (*print_table)(struct _Hash_l *this);              /* Prints Hashtable */
    void (*grow)(struct _Hash_l *this);                     /* Doubles the size of hashtable */
    void (*insert)(struct _Hash_l *this, Logic_Node *item); /* Inserts a new node into hashtable. */
    void (*delete)(struct _Hash_l *this, char *key);        /* Deletes node of key */

    Logic_Node **table; /* Array of Logic Node Pointers */
    int size;           /* size of table */
    int count;          /* number of nodes hash into table */

} Hash_l;
Hash_l *CREATE_HASH_L(int size);
#endif /* HASH_L_H */
