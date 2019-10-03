
/**
*  Rect_Node.c
*/

#include <SDL2/SDL.h>
#include "Rect_Node.h"
#include "Header.h"

static void _destroy(Rect_Node* this)
{
    if (NULL != this) {
        if (PRINT)
            printf("%p\n", this);
        free(this);
    }
}

static void _print(Rect_Node* this, const char* message)
{
    printf("Rect_Node: %p  %s\n", this, message);
}

Rect_Node* CREATE_RECT_NODE(SDL_Rect** rect)
{
    Rect_Node* this = malloc(sizeof(*this));
    this->destroy   = _destroy;
    this->print     = _print;

    this->rect = rect;
    this->next = NULL;

    if (PRINT)
        printf("%p\n", this);

    return this;
}
