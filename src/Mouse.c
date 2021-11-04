#include <SDL2/SDL.h>
#include "Header.h"
#include "Mouse.h"

static void _destroy(Mouse* this)
{
    if (NULL == this) {
        if (PRINT)
            printf("%p\n", this);
        free(this);
    }
}

static int _get_x(Mouse* this)
{
    int result;
    result = this->x % WINDOW_WIDTH;
    result = this->x - result;
    return result;
}

static int _get_y(Mouse* this)
{
    int result;
    result = this->y % WINDOW_HEIGHT;
    result = this->y - result;
    return result;
}

static int _on_click(Mouse* this, int state)
{
    if (this->lock && SDL_BUTTON(SDL_BUTTON_LEFT) && !state) {
        this->clk_x = this->get_x(this);
        this->clk_y = this->get_y(this);
        this->bool  = 1;
        return 1;
    }
    return 0;
}

static void _get_state(Mouse* this)
{
    this->lock = SDL_GetMouseState(&this->x, &this->y);
    MOUSE_X    = this->x;
    MOUSE_Y    = this->y;
}

Mouse* CREATE_MOUSE(int rect_size)
{
    Mouse* this = malloc(sizeof(*this));

    this->destroy   = _destroy;
    this->get_x     = _get_x;
    this->get_y     = _get_y;
    this->on_click  = _on_click;
    this->get_state = _get_state;

    this->rect_size = rect_size;
    this->bool      = 0;
    if (PRINT)
        printf("%p\n", this);

    return this;
}
