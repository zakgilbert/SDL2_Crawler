
/**
*  Hero.c
*/

#include <SDL2/SDL.h>
#include "Hero.h"
#include "Header.h"
#include "Sprite.h"
#include "Calc.h"
#include "Graphics.h"
#include "Direction.h"

static int get_mouse_angle(Hero* this)
{
    return ((int)(get_degree_angle(
                      get_radian_angle(MOUSE_X, MOUSE_Y,
                          mid(this->col_rect->x, this->col_rect->w),
                          mid(this->col_rect->y, this->col_rect->h)))
        / 22.5f));
}
static Sprite* current_sprite(Hero* this) { return this->sprites[this->cur_sprite]; }
static int compare_with_current(Hero* this, int key) { return (current_sprite(this) == this->sprites[this->cur_sprite]); }
/**
 * Private
 * Return the proper sprite state for hero type
 */
static int check_hero_state(Hero* this)
{
    if (IN_ACTION) {
        return this->cur_sprite;
    }
    if (STANCE_F(true) && !IN_ACTION) {
        this->ready = !this->ready;
    }
    MOUSE_ANGLE = get_mouse_angle(this);
    if (WALK_F(false)) {
        if (this->ready)
            return WALK_RDY_H;
        return WALK_H;
    }
    if (ATTACK_1_F(true) && this->ready) {
        return ATTACK_ONE_H;
    }
    if (ATTACK_2_F(true) && this->ready) {
        return ATTACK_TWO_H;
    }
    if (RUN_F(false)) {
        return RUN_H;
    }
    if (this->ready)
        return STAND_RDY_H;
    return STAND_H;
}
static void set_array_null(Sprite** sprites, int num)
{
    for (int i = 0; i < num; i++) {
        sprites[i] = NULL;
    }
}

static void _destroy(Hero* this)
{
    if (NULL != this) {
        SDL_DestroyTexture(this->texture);

        for (int i = 0; i < this->num_sprite; i++) {
            this->sprites[i]->destroy(this->sprites[i]);
        }

        if (PRINT)
            printf("%p\n", this);
        free(this);
    }
}

static void _print(Hero* this, const char* message)
{
    printf("Hero: %p  %s\n", this, message);
}

static char* _render(void* obj, SDL_Renderer* renderer)
{
    Hero* this      = (Hero*)obj;
    Sprite* current = this->sprites[this->cur_sprite];

    current->render(current, renderer);
    SDL_RenderDrawRect(renderer, this->col_rect);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderDrawPoint(renderer, this->col_rect->x, this->col_rect->y);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    return this->key;
}

static char* _logic(void* obj)
{
    Hero* this       = (Hero*)obj;
    this->cur_sprite = check_hero_state(this);
    Sprite* current  = this->sprites[this->cur_sprite];
    IN_ACTION        = current->logic(current);
    this->col_rect   = &current->rect;
    HERO_WIDTH       = this->col_rect->x + (this->col_rect->w / 2);
    HERO_HEIGHT      = this->col_rect->y + (this->col_rect->h / 2);

    return this->key;
}

static void _deallocate(void* obj)
{
    Hero* this = (Hero*)obj;
    this->destroy(this);
}
static void _add_sprite(Hero* this, Sprite* sprite, int key)
{
    this->sprites[key] = sprite;
    if ((-1) == (this->cur_sprite)) {
        this->cur_sprite = key;
        this->col_rect   = &this->sprites[key]->rect;
    }
}
Hero* CREATE_HERO(char* key, int num_sprite)
{
    Hero* this = malloc(sizeof(*this));

    this->destroy    = _destroy; /* Free Allocated Memory */
    this->print      = _print;   /* Print address of Hero type with message */
    this->render     = _render;  /* Render function */
    this->logic      = _logic;   /* Logic Function */
    this->deallocate = _deallocate;
    this->add_sprite = _add_sprite; /* Add a sprite sheet to class */

    this->cur_sprite = -1;
    this->num_sprite = num_sprite;

    this->key       = key;
    this->moving    = 0;
    this->in_action = 0;
    this->ready     = 0;

    this->sprites = malloc(sizeof(Sprite*) * this->num_sprite);
    set_array_null(this->sprites, this->num_sprite);

    if (PRINT)
        printf("%p\n", this);

    return this;
}
