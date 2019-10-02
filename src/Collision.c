
/**
*  Collision.c
*/

#include <SDL2/SDL.h>
#include "Collision.h"
#include "Header.h"
#include "Rect_Node.h"

static void _destroy(Collision* this)
{
    if (NULL != this) {
        if (PRINT)
            this->print(this, "Freeing");

        Rect_Node* temp = NULL;
        while (this->head) {
            temp       = this->head;
            this->head = this->head->next;
            temp->destroy(temp);
        }
        free(this);
    }
}

static void _print(Collision* this, const char* message)
{
    printf("Collision: %p  %s\n", this, message);
}

char* _render(void* obj, SDL_Renderer* renderer)
{
    Collision* this = (Collision*)obj;
    SDL_RenderDrawRect(renderer, this->inter);
    return this->key;
}

char* _logic(void* obj)
{
    Collision* this = (Collision*)obj;
    /*
    static int x, y;
    if ((SDL_FALSE == SDL_HasIntersection(this->ref, this->head->rect))) {
        x         = X;
        y         = Y;
        COLLIDING = 0;
    } else {
        X         = x;
        Y         = y;
        COLLIDING = 1;
    }
*/
    return this->key;
}

static void _add(Collision* this, Rect_Node* node)
{
    Rect_Node* current;
    if (!this->head) {
        this->head = node;
    } else {
        current = this->head;
        while (current) {
            current = current->next;
        }
        current = node;
    }
}

Collision* CREATE_COLLISION(char* key, SDL_Rect* ref)
{
    Collision* this = malloc(sizeof(*this));
    this->destroy   = _destroy;
    this->print     = _print;
    this->render    = _render;
    this->logic     = _logic;
    this->add       = _add;

    this->ref  = ref;
    this->head = NULL;
    this->key  = key;

    if (PRINT)
        this->print(this, "Allocating");

    return this;
}
