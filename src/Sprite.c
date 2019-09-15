
/**
*  Sprite.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Sprite.h"
#include "Header.h"
#include "Graphics.h"

static void _destroy(Sprite *this)
{
    if (NULL != this)
    {
        this->print(this);
        printf("%*s\n", 10, "Delete Sprite");
        free(this);
    }
}

static void _print(Sprite *this)
{
    printf("%p", this);
}

static void _render(void *obj, SDL_Renderer *renderer)
{
    Sprite *this = (Sprite *)obj;
    SDL_RenderCopy(renderer, this->texture, this->frame, &this->rect);
}

static double get_radian_angle(Sprite *this)
{
    double pi = 3.14159;
    typedef struct _point
    {
        int x;
        int y;
    } point;
    point p1 = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    point p2 = {MOUSE_X, MOUSE_Y};

    double delta_X = (double)(p1.x - p2.x);
    double delta_Y = (double)(p2.y - p1.y);
    double result = atan2(delta_X, delta_Y);
    return (result * (180 / pi));
}

static double get_degree_angle(double angle)
{
    double dif = 0.0f;
    if (angle < 0.0f)
    {
        dif = (abs(abs(angle) - 180.0f));
        dif += 180.0f;
    }
    else
    {
        dif = angle;
    }
    return dif;
}

static void _logic(void *obj)
{
    Sprite *this = (Sprite *)obj;

    if (FRAMES_RENDERED % 7 == 0)
    {
        this->row_index++;
        this->col_index++;

        if (this->row_index % this->rows == 0 && this->row_index != 0)
        {
            this->col_index = 0;
            this->row_index -= this->rows;
        }
        double angle = get_radian_angle(this);
        MOUSE_ANGLE = (int)(get_degree_angle(angle) / 22.0f);

        this->row_index = (MOUSE_ANGLE * this->rows) + this->col_index;

        if (this->row_index >= this->num_frames)
            this->row_index = 0 + this->col_index;
        this->frame = this->rects[this->row_index];
    }
}

Sprite *CREATE_SPRITE(SDL_Renderer *renderer, char *path, int rows, int cols, int w, int h, int type)
{
    Sprite *this = malloc(sizeof(*this));

    int x = 0;
    int y = 0;

    this->print = _print;
    this->destroy = _destroy;
    this->render = _render;
    this->logic = _logic;
    this->num_frames = rows * cols;
    this->type = type;
    this->texture = create_texture(renderer, path, &this->rect);
    this->rect.x = get_middle_x(WINDOW_WIDTH, w);
    this->rect.y = get_middle_y(WINDOW_HEIGHT, h);
    this->rect.w = w;
    this->rect.h = h;
    this->cols = cols;
    this->rows = rows;
    this->row_index = 0;
    this->col_index = 0;
    this->rects = malloc(sizeof(struct SDL_Rect *) * this->num_frames);

    for (int i = 0; i < this->num_frames; i++)
    {
        this->rects[i] = malloc(sizeof(struct SDL_Rect));
        if (x >= (w * rows))
        {
            y += h;
            x = 0;
        }
        this->rects[i]->x = x;
        this->rects[i]->y = y;
        this->rects[i]->w = w;
        this->rects[i]->h = h;
        x += w;
    }
    this->frame = this->rects[0];
    return this;
}
