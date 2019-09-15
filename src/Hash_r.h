#ifndef HASH_R_H
#define HASH_R_H

typedef struct _Render_Node Render_Node;

/**
 * A Hashtable of type render (a hash table that stores render nodes)
 * To change the stored data types, edit the nodes fields in Render_Node.h
 */
typedef struct _Hash_r
{
    void (*destroy)(struct _Hash_r *this);                   /* Frees allocated memory */
    Render_Node *(*search)(struct _Hash_r *this, char *key); /* Performs a hash search for the given key */
    void (*print_table)(struct _Hash_r *this);               /* Prints Hashtable */
    void (*grow)(struct _Hash_r *this);                      /* Doubles the size of hashtable */
    void (*insert)(struct _Hash_r *this, Render_Node *item); /* Inserts a new node into hashtable. */
    void (*delete)(struct _Hash_r *this, char *key);         /* Deletes node of key */

    Render_Node **table; /* Array of Logic Node Pointers */
    int size;            /* size of table */
    int count;           /* number of nodes hash into table */
} Hash_r;
Hash_r *CREATE_HASH_R(int size);
#endif /* HASH_R_H */
