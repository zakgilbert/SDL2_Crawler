
/**
*  Enemy.c
*/

#include <SDL2/SDL.h>
#include "Enemy.h"
#include "Header.h"
#include "Sprite.h"
#include "Calc.h"

static Sprite* get_stand(Enemy* this) { return this->sprites[STAND]; }              /* Get standing sprite */
static Sprite* get_walk(Enemy* this) { return this->sprites[WALK]; }                /* Get walking sprite */
static Sprite* get_run(Enemy* this) { return this->sprites[RUN]; }                  /* Get running sprite */
static Sprite* get_attack(Enemy* this) { return this->sprites[ATTACK]; }            /* Get sprite */
static Sprite* get_current(Enemy* this) { return this->sprites[this->cur_sprite]; } /* Get current sprite */

static void move_enemy(Sprite* sprite, Enemy* this)
{

    int speed         = 1;
    int direction     = this->angle;
    sprite->row_index = (this->angle * sprite->rows) + sprite->col_index;
    switch (direction) {
    case 0:
    case 8:
        (*sprite->y_origin) += speed;
        break;
    case 1:
        (*sprite->x_origin) -= speed;
        (*sprite->y_origin) += speed;
        break;
    case 2:
        (*sprite->x_origin) -= speed;
        break;
    case 3:
        (*sprite->x_origin) -= speed;
        (*sprite->y_origin) -= speed;
        break;
    case 4:
        (*sprite->y_origin) -= speed;
        break;
    case 5:
        (*sprite->x_origin) += speed;
        (*sprite->y_origin) -= speed;
        break;
    case 6:
        (*sprite->x_origin) += speed;
        break;
    case 7:
        (*sprite->x_origin) += speed;
        (*sprite->y_origin) += speed;
        break;

    default:
        break;
    }
}
static void set_array_null(Sprite** sprites, int num)
{
    for (int i = 0; i < num; i++) {
        sprites[i] = NULL;
    }
}

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
    Enemy* this     = (Enemy*)obj;
    Sprite* current = this->sprites[this->cur_sprite];
    current->render(current, renderer);

    return this->key;
}

static char* _logic(void* obj)
{
    Enemy* this = (Enemy*)obj;
    Sprite* current;
    
    if (!COLLIDING) {
        this->cur_sprite = WALK;
        current          = this->sprites[this->cur_sprite];
        this->angle      = (int)(get_degree_angle(get_radian_angle(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, current->rect.x, current->rect.y)) / 45.0f);
        move_enemy(current, this);
    } else if (COLLIDING) {
        this->cur_sprite = STAND;
        current          = this->sprites[this->cur_sprite];
    }

    current->rect.x = (*current->x_origin) + X;
    current->rect.y = (*current->y_origin) + Y;
    current->logic(current);
    this->col_rect = &current->rect;
    return this->key;
}

static void _add_sprite(Enemy* this, Sprite* sprite, int key)
{
    this->sprites[key] = sprite;
    if ((-1) == (this->cur_sprite)) {
        this->cur_sprite = key;
        this->col_rect   = &this->sprites[this->cur_sprite]->rect;
    }
}
Enemy* CREATE_ENEMY(char* key, int num_sprite, int* x, int* y)
{
    Enemy* this = malloc(sizeof(*this));

    this->destroy    = _destroy;    /* Free Allocated Memory */
    this->print      = _print;      /* Print address of Enemy type with message */
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
