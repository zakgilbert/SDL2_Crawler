#ifndef HASH_R_H
#define HASH_R_H

typedef struct _Render_Node Render_Node;

/**
 * A Hash_rtable
 * To change the stored data types, edit the nodes fields in Render_Node.h
 * A hashtable instance can be declared as follows...
 *      Hash_r * hash_table = CREATE_HASH(int size)
 */
typedef struct _Hash_r
{
    /**
     * Deallocates all memory that of which was allocated at the hashtables creation.
     */
    void (*destroy)(struct _Hash_r *this);

    /**
     * Performs a hash search for the given key
     */
    Render_Node *(*search)(struct _Hash_r *this, char *key);

    /**
     * Prints Hash_rtable
     */
    void (*print_table)(struct _Hash_r *this);

    void (*grow)(struct _Hash_r *this);
    /**
     * Inserts a new node into hashtable.
     */
    void (*insert)(struct _Hash_r *this, Render_Node *item);

    /**
     * Deletes node of key
     */
    void (*delete)(struct _Hash_r *this, char *key);

    Render_Node **table;
    int size;
    int count;

} Hash_r;
Hash_r *CREATE_HASH_R(int size);
#endif /* HASH_R_H */
