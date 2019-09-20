
/**
*  Enemy.c
*/

#include <SDL2/SDL.h>
#include "Enemy.h"
#include "Header.h"
#include "Sprite.h"

static void _destroy(Enemy* this)
{
    if (NULL != this) {
        this->print(this, "Freeing");
        SDL_DestroyTexture(this->texture);

        while (*(++this->sprites))
            (*this->sprites)->destroy((*this->sprites));

        free(this);
    }
}

static void _print(Enemy* this, const char* message)
{
    printf("Enemy: %p  %s\n", this, message);
}
static char* _render(void* obj, SDL_Renderer* renderer)
{
    Enemy* this = (Enemy*)obj;
}
static char* _logic(void* obj)
{
}
static void _add_sprite(Enemy* this, Sprite* sprite)
{
    
}
Enemy* CREATE_ENEMY(char* key)
{
    Enemy* this = malloc(sizeof(*this));

    this->destroy    = _destroy;    /* Free Allocated Memory */
    this->print      = _print;      /* Print address of Enemy type with message */
    this->render     = _render;     /* Render function */
    this->logic      = _logic;      /* Logic Function */
    this->add_sprite = _add_sprite; /* Add a sprite sheet to class */

    this->cur_sprite = -1;
    this->num_sprite = 0;

    if (PRINT)
        this->print(this, "Allocating");

    return this;
}
