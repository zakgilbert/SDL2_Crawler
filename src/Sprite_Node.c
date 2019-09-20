
/**
*  Sprite_Node.c
*/

#include "stdio.h"
#include "Sprite_Node.h"
#include "Header.h"
#include "Sprite.h"

static void _destroy(Sprite_Node* this)
{
    if (NULL != this) {
        this->print(this, "Freeing");
        this->sprite->destroy(this->sprite);
        free(this);
    }
}

static void _print(Sprite_Node* this, const char* message)
{
    printf("Sprite_Node: %p  %s\n", this, message);
}

Sprite_Node* CREATE_SPRITE_NODE(Sprite* sprite)
{
    Sprite_Node* this = malloc(sizeof(*this));
    this->destroy     = _destroy;
    this->print       = _print;

    this->sprite = sprite;
    this->next   = NULL;

    if (PRINT)
        this->print(this, "Allocating");

    return this;
}
