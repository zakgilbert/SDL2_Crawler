#include <SDL2/SDL.h>
#include "Graphics.h"
#include "Input.h"
#include "Header.h"
#include "Sprite.h"
static int rand_range(int low, int up)
{
    return (rand() % (up - low + 1)) + low;
}

/**
 * Private
 * Return the angle between two points in radians
 */
static double get_radian_angle(Sprite* this)
{
    typedef struct _point {
        int x;
        int y;
    } point;
    point p1 = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
    point p2 = { MOUSE_X, MOUSE_Y };

    double delta_X = (double)(p1.x - p2.x);
    double delta_Y = (double)(p2.y - p1.y);
    double result  = atan2(delta_X, delta_Y);
    return (result * (180 / PI));
}

/**
 * Private
 * Convert radian to degrees
 */
static double get_degree_angle(double angle)
{
    double dif = 0.0f;
    if (angle < 0.0f) {
        dif = (abs(abs(angle) - 180.0f));
        dif += 180.0f;
    } else {
        dif = angle;
    }
    return dif;
}

static int bounds(int* x, int* y, int direction, Sprite* this)
{
    int result = direction;
    if ((*y) < 0) {
        if (direction == 3) {
            result = 1;
        } else if (direction == 5) {
            result = 7;
        } else
            result = 0;
        printf("ret: %d\n", 1);
    } else if ((*x) < 0) {
        if (direction == 3) {
            result = 5;
        } else if (direction == 1) {
            result = 7;
        } else
            result = 6;
        printf("ret: %d\n", 2);
    } else if ((*x) > 2048 - (WINDOW_WIDTH - this->rect.w)) {
        if (direction == 5) {
            result = 3;
        } else if (direction == 7) {
            result = 1;
        } else
            result = 2;
        printf("ret: %d\n", 3);
    } else if ((*y) > 1792 - (WINDOW_HEIGHT - this->rect.h)) {
        if (direction == 1) {
            result = 3;
        } else if (direction == 7) {
            result = 1;
        } else
            result = 4;
        printf("ret: %d\n", 4);
    }
    return result;
}

/**
 * Private
 * Return the proper sprite state for hero type
 */
static char* check_hero_state(Sprite* this)
{
    if (KEY == W)
        return this->walk;
    else if (KEY == A)
        return this->attack_1;
    else if (KEY == S)
        return this->run;
    else if (KEY == D)
        return this->attack_2;
    else if (KEY == NON)
        return this->stand;
    return this->path;
}

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
        this->print(this);
        printf("%*s\n", 10, "Delete Sprite");
        free(this);
    }
}

static void _print(Sprite* this)
{
    printf("%p", this);
}

static char* _render(void* obj, SDL_Renderer* renderer)
{
    Sprite* this = (Sprite*)obj;
    SDL_RenderCopy(renderer, this->texture, this->frame, &this->rect);
    return this->path;
}

static char* _logic_attack_enemy(void* obj)
{
    Sprite* this = (Sprite*)obj;

    if (!this->action_started) {
        this->row_index -= this->col_index;
        this->action_started = 1;
    }
    if (FRAMES_RENDERED % 3 == 0) {
        this->row_index++;
        this->col_index++;

        if (this->row_index % this->rows == 0 && this->row_index != 0) {
            this->col_index = 0;
            this->row_index -= this->rows;
            IN_ATTACK_ONE = 0;
            IN_ATTACK_TWO = 0;
        }

        MOUSE_ANGLE     = (int)(get_degree_angle(get_radian_angle(this)) / 22.0f);
        this->row_index = (MOUSE_ANGLE * this->rows) + this->col_index;

        if (this->row_index >= this->num_frames)
            this->row_index = 0 + this->col_index;
        this->frame = this->rects[this->row_index];
    }
    return this->path;
}
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
static char* _logic_movement_enemy(void* obj)
{
    Sprite* this = (Sprite*)obj;

    if (FRAMES_RENDERED % 3 == 0) {
        this->row_index++;
        this->col_index++;

        if (this->row_index % this->rows == 0 && this->row_index != 0) {
            this->col_index = 0;
            this->row_index -= this->rows;
        }
        MOUSE_ANGLE     = (int)(get_degree_angle(get_radian_angle(this)) / 22.0f);
        this->row_index = (MOUSE_ANGLE * this->rows) + this->col_index;

        if (this->row_index >= this->num_frames)
            this->row_index = 0 + this->col_index;
        this->frame = this->rects[this->row_index];
    }
    return check_hero_state(this);
}

static char* _logic_attack_hero(void* obj)
{
    Sprite* this = (Sprite*)obj;

    if (!this->action_started) {
        this->row_index -= this->col_index;
        this->action_started = 1;
    }
    if (FRAMES_RENDERED % 3 == 0) {
        this->row_index++;
        this->col_index++;

        if (this->row_index % this->rows == 0 && this->row_index != 0) {
            this->col_index = 0;
            this->row_index -= this->rows;

            return check_hero_state(this);
        }

        MOUSE_ANGLE     = (int)(get_degree_angle(get_radian_angle(this)) / 22.0f);
        this->row_index = (MOUSE_ANGLE * this->rows) + this->col_index;

        if (this->row_index >= this->num_frames)
            this->row_index = 0 + this->col_index;
        this->frame = this->rects[this->row_index];
    }
    return this->path;
}

static char* _logic_movement_hero(void* obj)
{
    Sprite* this = (Sprite*)obj;

    if (FRAMES_RENDERED % 3 == 0) {
        this->row_index++;
        this->col_index++;

        if (this->row_index % this->rows == 0 && this->row_index != 0) {
            this->col_index = 0;
            this->row_index -= this->rows;
        }
        MOUSE_ANGLE     = (int)(get_degree_angle(get_radian_angle(this)) / 22.0f);
        this->row_index = (MOUSE_ANGLE * this->rows) + this->col_index;

        if (this->row_index >= this->num_frames)
            this->row_index = 0 + this->col_index;
        this->frame = this->rects[this->row_index];
    }
    return check_hero_state(this);
}

Sprite* CREATE_SPRITE(SDL_Renderer* renderer, char* path,
    int rows, int cols, int* x, int* y, int w, int h,
    int state, int type, char* walk, char* stand, char* run, char* attack_1, char* attack_2)
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
        this->stand    = stand;
        this->walk     = walk;
        this->run      = run;
        this->attack_1 = attack_1;
        this->attack_2 = attack_2;
        this->rect.x   = get_middle_x(WINDOW_WIDTH, w);
        this->rect.y   = get_middle_y(WINDOW_HEIGHT, h);

        if (this->state == MOVEMENT)
            this->logic = _logic_movement_hero;
        else if (this->state == ACTION)
            this->logic = _logic_attack_hero;

    } else if (type == ENEMY) {
        this->stand    = stand;
        this->walk     = walk;
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

    this->path              = path;
    this->current_direction = 0;
    set_sprite_cords(this);

    this->frame = this->rects[0];
    return this;
}
