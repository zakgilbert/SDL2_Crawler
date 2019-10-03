#include <SDL2/SDL.h>
#include "Graphics.h"
#include "Input.h"
#include "Header.h"
#include "Sprite.h"
#include "Calc.h"

/**
 * Set proper coordinates of each frame
 */
static void set_sprite_cords(Sprite* this)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < this->num_frames; i++) {
        this->rects[i] = malloc(sizeof(struct SDL_Rect));
        if (x >= (this->rect.w * this->rows)) {
            y += this->rect.h;
            x = 0;
        }
        this->rects[i]->x = x;
        this->rects[i]->y = y;
        this->rects[i]->w = this->rect.w;
        this->rects[i]->h = this->rect.h;
        x += this->rect.w;
    }
}

static void _destroy(Sprite* this)
{
    if (NULL != this) {
        if (PRINT)
            printf("%p\n", this);
        free(this);
    }
}

static void _print(Sprite* this)
{
    printf("%p   ", this);
}

static int _render(void* obj, SDL_Renderer* renderer)
{
    Sprite* this = (Sprite*)obj;
    SDL_RenderCopy(renderer, this->texture, this->frame, &this->rect);
    return 0;
}

static int _logic_attack_enemy(void* obj)
{
    Sprite* this = (Sprite*)obj;
    if (FRAMES_RENDERED % 3 == 0) {
        if (this->col_index == 6) {
            OPEN_FOR_ATK = 1;
        } else {
            OPEN_FOR_ATK = 0;
        }

        this->row_index++;
        this->col_index++;

        if (this->row_index % this->rows == 0 && this->row_index != 0) {
            this->col_index = 0;
            this->row_index -= this->rows;
            return 0;
        }

        if (this->row_index >= this->num_frames)
            this->row_index = 0 + this->col_index;
        this->frame = this->rects[this->row_index];
    }
    return 1;
}
static int _logic_movement_enemy(void* obj)
{
    Sprite* this = (Sprite*)obj;

    if (FRAMES_RENDERED % 3 == 0) {
        this->row_index++;
        this->col_index++;

        if (this->row_index % this->rows == 0 && this->row_index != 0) {
            this->col_index = 0;
            this->row_index -= this->rows;
            return 1;
        }

        if (this->row_index >= this->num_frames)
            this->row_index = 0 + this->col_index;
        this->frame = this->rects[this->row_index];
    }
    return 0;
}

static int _logic_attack_hero(void* obj)
{
    Sprite* this = (Sprite*)obj;

    if (FRAMES_RENDERED % 3 == 0) {
        this->row_index++;
        this->col_index++;

        if (this->row_index % this->rows == 0 && this->row_index != 0) {
            this->col_index = 0;
            this->row_index -= this->rows;

            return 0;
        }
        this->row_index = (MOUSE_ANGLE * this->rows) + this->col_index;
        if (this->row_index >= this->num_frames)
            this->row_index = 0 + this->col_index;
        this->frame = this->rects[this->row_index];
    }
    return 1;
}

static int _logic_movement_hero(void* obj)
{
    Sprite* this = (Sprite*)obj;

    if (FRAMES_RENDERED % 3 == 0) {
        this->row_index++;
        this->col_index++;

        if (this->row_index % this->rows == 0 && this->row_index != 0) {
            this->col_index = 0;
            this->row_index -= this->rows;
        }
        this->row_index = (MOUSE_ANGLE * this->rows) + this->col_index;

        if (this->row_index >= this->num_frames)
            this->row_index = 0 + this->col_index;
        this->frame = this->rects[this->row_index];
    }
    return 0;
}

Sprite* CREATE_SPRITE(SDL_Renderer* renderer, char* path,
    int rows, int cols, int* x, int* y, int w, int h,
    int state, int type)
{
    Sprite* this = malloc(sizeof(*this));
    this->state  = state;
    this->type   = type;

    this->print    = _print;
    this->destroy  = _destroy;
    this->render   = _render;
    this->x_origin = x;
    this->y_origin = y;

    if (type == HERO) {
        this->rect.x = get_middle_x(WINDOW_WIDTH, w);
        this->rect.y = get_middle_y(WINDOW_HEIGHT, h);
        HERO_WIDTH   = w / 2;
        HERO_HEIGHT  = h / 2;

        if (this->state == MOVEMENT)
            this->logic = _logic_movement_hero;
        else if (this->state == ACTION)
            this->logic = _logic_attack_hero;

    } else if (type == ENEMY) {
        this->x_origin = x;
        this->y_origin = y;
        this->rect.x   = (*this->x_origin);
        this->rect.y   = (*this->y_origin);

        if (this->state == MOVEMENT)
            this->logic = _logic_movement_enemy;
        else if (this->state == ACTION)
            this->logic = _logic_attack_enemy;
    }
    this->num_frames     = rows * cols;
    this->texture        = create_texture(renderer, path, &this->rect);
    this->rect.w         = w;
    this->rect.h         = h;
    this->cols           = cols;
    this->rows           = rows;
    this->row_index      = 0;
    this->col_index      = 0;
    this->action_started = 0;
    this->moving         = 0;
    this->time_begin     = 0;
    this->time_end       = 0;
    this->rects          = malloc(sizeof(struct SDL_Rect*) * this->num_frames);

    this->current_direction = 0;
    set_sprite_cords(this);

    this->frame = this->rects[0];
    if (PRINT)
        printf("%p\n", this);
    return this;
}
