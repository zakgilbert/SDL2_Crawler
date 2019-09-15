#ifndef LOGIC_NODE_H
#define LOGIC_NODE_H
typedef void logic_function(void *obj);
typedef struct _Logic_Node
{
    void (*destroy)(struct _Logic_Node *this);
    void (*print)(struct _Logic_Node *this, int i);
    void *obj;
    logic_function(*funct);
    int index;
    char * key;
} Logic_Node;
Logic_Node *CREATE_LOGIC_NODE(char *key, void *obj, logic_function funct);

#endif /* LOGIC_NODE_H */
