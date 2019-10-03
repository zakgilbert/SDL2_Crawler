#include <SDL2/SDL.h>
#include "Header.h"
#include "Logic_Node.h"

static void _destroy(Logic_Node* this)
{
    if (NULL != this) {
        if (this->deallocation_f) {
            (*this->deallocation_f)(this->obj);
        }
        if (PRINT) {
            printf("%p\n", this);
        }
        free(this);
    }
}
static void _print(Logic_Node* node, int i)
{
    printf("%p     Data: %*p     Key: %*s    Index: %*d", node, 2, node->funct, 10, node->key, 2, i);
}
Logic_Node* CREATE_LOGIC_NODE(char* key, void* obj, logic_function funct, deallocation_function deallocation_f)
{
    Logic_Node* this     = malloc(sizeof(*this));
    this->destroy        = _destroy;
    this->print          = _print;
    this->key            = key;
    this->obj            = obj;
    this->funct          = funct;
    this->deallocation_f = deallocation_f;

    if (PRINT) {
        printf("%p\n", this);
    }
    return this;
}