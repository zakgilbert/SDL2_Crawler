#include <SDL2/SDL.h>
#include "Graphics.h"
#include "Header.h"
#include "Sprite.h"

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

static void _render(void* obj, SDL_Renderer* renderer)
{
    Sprite* this = (Sprite*)obj;
    SDL_RenderCopy(renderer, this->texture, this->frame, &this->rect);
}

static void _logic(void* obj)
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
}
Sprite* CREATE_SPRITE(SDL_Renderer* renderer, char* path, int rows, int cols, int w, int h, int type)
{
    Sprite* this = malloc(sizeof(*this));

    this->print      = _print;
    this->destroy    = _destroy;
    this->render     = _render;
    this->logic      = _logic;
    this->num_frames = rows * cols;
    this->type       = type;
    this->texture    = create_texture(renderer, path, &this->rect);
    this->rect.x     = get_middle_x(WINDOW_WIDTH, w);
    this->rect.y     = get_middle_y(WINDOW_HEIGHT, h);
    this->rect.w     = w;
    this->rect.h     = h;
    this->cols       = cols;
    this->rows       = rows;
    this->row_index  = 0;
    this->col_index  = 0;
    this->rects      = malloc(sizeof(struct SDL_Rect*) * this->num_frames);

    set_sprite_cords(this);

    this->frame = this->rects[0];
    return this;
}
