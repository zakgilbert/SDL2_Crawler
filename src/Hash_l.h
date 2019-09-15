#ifndef HASH_L_H
#define HASH_L_H

typedef struct SDL_Renderer SDL_Renderer;
typedef struct _Logic_Node Logic_Node;

typedef void render_function(void *obj, SDL_Renderer *renderer);
/**
 * A Hash_ltable
 * To change the stored data types, edit the nodes fields in Logic_Node.h
 * A hashtable instance can be declared as follows...
 *      Hash_l * hash_table = CREATE_HASH(int size)
 */
typedef struct _Hash_l
{
    /**
     * Deallocates all memory that of which was allocated at the hashtables creation.
     */
    void (*destroy)(struct _Hash_l *this);

    /**
     * Performs a hash search for the given key
     */
    Logic_Node *(*search)(struct _Hash_l *this, char *key);

    /**
     * Prints Hash_ltable
     */
    void (*print_table)(struct _Hash_l *this);

    void (*grow)(struct _Hash_l *this);
    /**
     * Inserts a new node into hashtable.
     */
    void (*insert)(struct _Hash_l *this, Logic_Node *item);

    /**
     * Deletes node of key
     */
    void (*delete)(struct _Hash_l *this, char *key);

    Logic_Node **table;
    int size;
    int count;

} Hash_l;
Hash_l *CREATE_HASH_L(int size);
#endif /* HASH_L_H */
