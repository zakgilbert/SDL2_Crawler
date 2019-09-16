#include <SDL2/SDL.h>
#include "Alpha_Node.h"
#include "Graphics.h"
#include "Header.h"

static void _destroy(Alpha_Node* this)
{
    if (NULL != this) {
        if (PRINT)
            printf("Destroy: %p\n", this);
        free(this);
    }
}

Alpha_Node* CREATE_ALPHA_NODE(char* key, char* path, SDL_Renderer* renderer)
{
    Alpha_Node* this = malloc(sizeof(*this));

    this->destroy = _destroy;
    this->key     = key;
    this->texture = create_texture(renderer, path, &this->rect);

    if (PRINT)
        printf("Create: %p\n", this);

    return this;
}
