#ifndef LOGIC_NODE_H
#define LOGIC_NODE_H

typedef char* logic_function(void* obj);
typedef void deallocation_function(void* obj);

/**
 * Encapsulate data for Logic_Table
 */
typedef struct _Logic_Node {
    void (*destroy)(struct _Logic_Node* this);      /* Free allocated memory */
    void (*print)(struct _Logic_Node* this, int i); /* Print node data */
    logic_function(*funct);                         /* Pointer to logic function */
    deallocation_function(*deallocation_f);         /* Call destroy on object */

    void* obj; /* Pointer to object whose logic function will be called */
    int index; /* Index the node is stored at */
    char* key; /* Key of node */
} Logic_Node;
Logic_Node* CREATE_LOGIC_NODE(char* key, void* obj, logic_function, deallocation_function);

#endif /* LOGIC_NODE_H */
