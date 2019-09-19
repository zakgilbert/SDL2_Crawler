
/**
*  Direction.c
*/

#include <SDL2/SDL.h>
#include "Direction.h"
#include "Header.h"

static void print(Direction* this)
{
    printf("%p", this);
}
static void _destroy(Direction* this)
{
    if (NULL != this) {
        if (PRINT) {
            print(this);
            printf("%*s\n", 10, "Delete");
        }
        free(this);
    }
}

void map_bounds()
{
    if (Y > 0)
        Y = 0;
    if (X > 0)
        X = 0;
    if (X < -2048 + WINDOW_WIDTH)
        X = -2048 + WINDOW_WIDTH;
    if (Y < -1792 + WINDOW_HEIGHT)
        Y = -1792 + WINDOW_HEIGHT;
}

static char* _render(void* obj, SDL_Renderer* renderer)
{
    Direction* this = (Direction*)obj;
    return this->key;
}

static char* _logic(void* obj)
{
    Direction* this = (Direction*)obj;
    if (KEY == W) {
        switch (MOUSE_ANGLE) {
        case 0:
        case 16:
            Y--;
            break;
        case 1:
            if (FRAMES_RENDERED % 2 == 0)
                X++;
            Y--;
            break;
        case 2:
            if (FRAMES_RENDERED % 1 == 0)
                Y--;
            X++;
            break;
        case 3:
            if (FRAMES_RENDERED % 2 == 0)
                Y--;
            X++;
            break;

        case 4:
            X++;
            break;
        case 5:
            if (FRAMES_RENDERED % 2 == 0)
                Y++;
            X++;
            break;
        case 6:
            if (FRAMES_RENDERED % 1 == 0)
                X++;
            Y++;
            break;
        case 7:
            if (FRAMES_RENDERED % 2 == 0)
                X++;
            Y++;
            break;

        case 8:
            Y++;
            break;
        case 9:
            if (FRAMES_RENDERED % 2 == 0)
                X--;
            Y++;
            break;
        case 10:
            if (FRAMES_RENDERED % 1 == 0)
                Y++;
            X--;
            break;
        case 11:
            if (FRAMES_RENDERED % 2 == 0)
                Y++;
            X--;
            break;
        case 12:
            X--;
            break;
        case 13:
            if (FRAMES_RENDERED % 2 == 0)
                Y--;
            X--;
            break;
        case 14:
            if (FRAMES_RENDERED % 1 == 0)
                X--;
            Y--;
            break;
        case 15:
            if (FRAMES_RENDERED % 2 == 0)
                X--;
            Y--;
            break;

        default:
            break;
        }
    }
    map_bounds();
    return this->key;
}
Direction* CREATE_DIRECTION(char* key)
{
    Direction* this = malloc(sizeof(*this));

    this->destroy = _destroy;
    this->logic   = _logic;
    this->render  = _render;

    this->key = key;

    if (PRINT)
        print(this);
    return this;
}
