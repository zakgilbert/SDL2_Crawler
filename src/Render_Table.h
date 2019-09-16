#ifndef RENDER_TABLE_H
#define RENDER_TABLE_H

typedef struct _Render_Node Render_Node;

/** 
 * Hash Render Nodes 
 */
typedef struct _Render_Table {
    void (*destroy)(struct _Render_Table* this);                   /* Free allocated memory */
    Render_Node* (*search)(struct _Render_Table* this, char* key); /* Perform a hash search for the given key */
    void (*print_table)(struct _Render_Table* this);               /* Print Hashtable */
    void (*grow)(struct _Render_Table* this);                      /* Double the size of hashtable */
    void (*insert)(struct _Render_Table* this, Render_Node* item); /* Insert a new node into hashtable. */
    void (*delete)(struct _Render_Table* this, char* key);         /* Delete node of key */

    Render_Node** table; /* Array of Logic Node Pointers */
    int size;            /* size of table */
    int count;           /* number of nodes hash into table */
} Render_Table;
Render_Table* CREATE_RENDER_TABLE(int size);
#endif /* RENDER_TABLE_H */
