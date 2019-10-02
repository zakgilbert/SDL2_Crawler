
/**
*  Tile.c
*/

#include <SDL2/SDL.h>
#include "Tile.h"
#include "Header.h"

static void _destroy(Tile* this)
{
    if (NULL != this) {
        if (PRINT)
            this->print(this, "Freeing");
        free(this);
    }
}

static void _print(Tile* this, const char* message)
{
    printf("Tile: %p  %s\n", this, message);
}

Tile* CREATE_TILE()
{
    Tile* this    = malloc(sizeof(*this));
    this->destroy = _destroy;
    this->print   = _print;

    if (PRINT)
        this->print(this, "Allocating");

    return this;
}
