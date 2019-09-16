#include <SDL2/SDL.h>
#include "Header.h"
#include "Logic_Node.h"

static void _destroy(Logic_Node* this)
{
    if (NULL != this) {
        if (PRINT) {
            this->print(this, this->index);
            printf("%*s\n", 10, "Delete");
        }
        free(this);
    }
}
static void _print(Logic_Node* node, int i)
{
    printf("%p     Data: %*p     Key: %*s    Index: %*d", node, 2, node->funct, 10, node->key, 2, i);
}
Logic_Node* CREATE_LOGIC_NODE(char* key, void* obj, logic_function funct)
{
    Logic_Node* this = malloc(sizeof(*this));
    this->destroy    = _destroy;
    this->print      = _print;
    this->key        = key;
    this->obj        = obj;
    this->funct      = funct;

    return this;
}
