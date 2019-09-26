
/**
*  Hero.c
*/

#include <SDL2/SDL.h>
#include "Hero.h"
#include "Header.h"
#include "Sprite.h"

static Sprite* get_stand(Hero* this) { return this->sprites[STAND]; }              /* Get standing sprite */
static Sprite* get_walk(Hero* this) { return this->sprites[WALK]; }                /* Get walking sprite */
static Sprite* get_run(Hero* this) { return this->sprites[RUN]; }                  /* Get running sprite */
static Sprite* get_attack(Hero* this) { return this->sprites[ATTACK]; }            /* Get sprite */
static Sprite* get_current(Hero* this) { return this->sprites[this->cur_sprite]; } /* Get current sprite */

static void move_enemy(Sprite* this)
{
    int direction = (this->row_index - this->col_index) / this->rows;
    int speed     = 1;
    switch (direction) {
    case 0:
    case 8:
        (*this->y_origin) += speed;
        break;
    case 1:
        (*this->x_origin) -= speed;
        (*this->y_origin) += speed;
        break;
    case 2:
        (*this->x_origin) -= speed;
        break;
    case 3:
        (*this->x_origin) -= speed;
        (*this->y_origin) -= speed;
        break;
    case 4:
        (*this->y_origin) -= speed;
        break;
    case 5:
        (*this->x_origin) += speed;
        (*this->y_origin) -= speed;
        break;
    case 6:
        (*this->x_origin) += speed;
        break;
    case 7:
        (*this->x_origin) += speed;
        (*this->y_origin) += speed;
        break;

    default:
        break;
    }
}
static set_array_null(Sprite** sprites, int num)
{
    for (int i = 0; i < num; i++) {
        sprites[i] = NULL;
    }
}

static void _destroy(Hero* this)
{
    if (NULL != this) {
        this->print(this, "Freeing");
        SDL_DestroyTexture(this->texture);

        while (*(++this->sprites))
            (*this->sprites)->destroy((*this->sprites));

        free(this);
    }
}

static void _print(Hero* this, const char* message)
{
    printf("Hero: %p  %s\n", this, message);
}

static char* _render(void* obj, SDL_Renderer* renderer)
{
    Hero* this     = (Hero*)obj;
    Sprite* current = this->sprites[this->cur_sprite];

    current->render(current, renderer);

    return this->key;
}

static char* _logic(void* obj)
{
    Hero* this      = (Hero*)obj;
    this->cur_sprite = WALK;
    Sprite* current  = this->sprites[this->cur_sprite];

    current->rect.x = (*this->x) + X;
    current->rect.y = (*this->x) + Y;
    current->logic(current);
    return this->key;
}

static void _add_sprite(Hero* this, Sprite* sprite, int key)
{
    this->sprites[key] = sprite;
    if ((-1) == (this->cur_sprite))
        this->cur_sprite = key;
}
Hero* CREATE_ENEMY(char* key, int num_sprite, int* x, int* y)
{
    Hero* this = malloc(sizeof(*this));

    this->destroy    = _destroy;    /* Free Allocated Memory */
    this->print      = _print;      /* Print address of Hero type with message */
    this->render     = _render;     /* Render function */
    this->logic      = _logic;      /* Logic Function */
    this->add_sprite = _add_sprite; /* Add a sprite sheet to class */

    this->cur_sprite = -1;
    this->num_sprite = num_sprite;

    this->key    = key;
    this->moving = 0;
    this->x      = x;
    this->y      = y;

    this->sprites = malloc(sizeof(Sprite*) * this->num_sprite);
    set_array_null(this->sprites, this->num_sprite);

    if (PRINT)
        this->print(this, "Allocating");

    return this;
}
