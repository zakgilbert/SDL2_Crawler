#include <SDL2/SDL.h>
#include "Header.h"
#include "Render_Node.h"

/**
 * Deallocates all memory that of which was allocated at the Render_Nodes creation.
 */
static void _destroy(Render_Node* this)
{
    if (NULL != this) {
        if (PRINT)
            printf("%p\n", this);
        free(this);
    }
}

/**
 * prints Render_Nodes data, key, address.
 */
static void _print(Render_Node* node, int i)
{
    printf("%p     Data: %*p     Key: %*s    Index: %*d", node, 2, node->funct, 10, node->key, 2, i);
}

Render_Node* CREATE_RENDER_NODE(char* key, void* obj, render_function funct)
{
    Render_Node* this = malloc(sizeof(*this));

    this->destroy = _destroy;
    this->print   = _print;

    this->key   = key;
    this->funct = funct;
    this->obj   = obj;
    if (PRINT)
        printf("%p\n", this);

    return this;
}
