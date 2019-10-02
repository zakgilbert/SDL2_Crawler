
/**
*  Direction.c
*/

#include <SDL2/SDL.h>
#include "Direction.h"
#include "Header.h"
#include "Calc.h"

static void fifteen()
{
    if (FRAMES_RENDERED % 2 == 0)
        X -= HERO_SPEED;
    Y -= HERO_SPEED;
}
static void forteen()
{
    if (FRAMES_RENDERED % 1 == 0)
        X -= HERO_SPEED;
    Y -= HERO_SPEED;
}
static void thirteen()
{
    if (FRAMES_RENDERED % 2 == 0)
        Y -= HERO_SPEED;
    X -= HERO_SPEED;
}
static void twelve()
{
    X -= HERO_SPEED;
}
static void eleven()
{
    if (FRAMES_RENDERED % 2 == 0)
        Y += HERO_SPEED;
    X -= HERO_SPEED;
}
static void ten()
{
    if (FRAMES_RENDERED % 1 == 0)
        Y += HERO_SPEED;
    X -= HERO_SPEED;
}
static void nine()
{
    if (FRAMES_RENDERED % 2 == 0)
        X -= HERO_SPEED;
    Y += HERO_SPEED;
}
static void eight()
{
    Y += HERO_SPEED;
}
static void seven()
{
    if (FRAMES_RENDERED % 2 == 0)
        X += HERO_SPEED;
    Y += HERO_SPEED;
}
static void six()
{
    if (FRAMES_RENDERED % 1 == 0)
        X += HERO_SPEED;
    Y += HERO_SPEED;
}
static void five()
{
    if (FRAMES_RENDERED % 2 == 0)
        Y += HERO_SPEED;
    X += HERO_SPEED;
}
static void four()
{
    X += HERO_SPEED;
}
static void three()
{
    if (FRAMES_RENDERED % 2 == 0)
        Y -= HERO_SPEED;
    X += HERO_SPEED;
}
static void two()
{
    if (FRAMES_RENDERED % 1 == 0)
        Y -= HERO_SPEED;
    X += HERO_SPEED;
}
static void one()
{
    if (FRAMES_RENDERED % 2 == 0)
        X += HERO_SPEED;
    Y -= HERO_SPEED;
}
static void zero()
{
    Y -= HERO_SPEED;
}
static void sixteen()
{
    Y -= HERO_SPEED;
}

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
    if (X < -MAP_W + WINDOW_WIDTH)
        X = -MAP_W + WINDOW_WIDTH;
    if (Y < -MAP_H + WINDOW_HEIGHT)
        Y = -MAP_H + WINDOW_HEIGHT;
}

static char* _render(void* obj, SDL_Renderer* renderer)
{
    Direction* this = (Direction*)obj;
    return this->key;
}
static void col_down()
{
    switch (MOUSE_ANGLE) {
    case 3:
        three();
        break;
    case 4:
        four();
        break;
    case 5:
        five();
        break;
    case 6:
        six();
        break;
    case 7:
        seven();
        break;
    case 8:
        eight();
        break;
    case 9:
        nine();
        break;
    case 10:
        ten();
        break;
    case 11:
        eleven();
        break;
    case 12:
        twelve();
        break;
    case 13:
        thirteen();
        break;
    case 14:
        forteen();
        break;
    default:
        break;
    }
}
static int down()
{
    int dirs[5] = { 0, 1, 2, 15, 16 };
    for (int i = 0; i < 5; i++) {
        if (dirs[i] == MOUSE_ANGLE)
            return 1;
    }
    return 0;
}
static int up()
{
    int dirs[4] = { 6, 7, 8, 9 };
    for (int i = 0; i < 4; i++) {
        if (dirs[i] == MOUSE_ANGLE)
            return 1;
    }
    return 0;
}
static void col_up()
{
    switch (MOUSE_ANGLE) {
    case 0:
        zero();
        break;
    case 1:
        one();
        break;
    case 2:
        two();
        break;
    case 3:
        three();
        break;
    case 4:
        four();
        break;
    case 5:
        five();
        break;
    case 10:
        ten();
        break;
    case 11:
        eleven();
        break;
    case 12:
        twelve();
        break;
    case 13:
        thirteen();
        break;
    case 14:
        forteen();
        break;
    case 15:
        fifteen();
        break;
    case 16:
        sixteen();
        break;
    default:
        break;
    }
}
static int right()
{
    int dirs[4] = { 10, 11, 12, 13 };
    for (int i = 0; i < 4; i++) {
        if (dirs[i] == MOUSE_ANGLE)
            return 1;
    }
    return 0;
}

static void col_right()
{
    switch (MOUSE_ANGLE) {
    case 0:
        zero();
        break;
    case 1:
        one();
        break;
    case 2:
        two();
        break;
    case 3:
        three();
        break;
    case 4:
        four();
        break;
    case 5:
        five();
        break;
    case 6:
        six();
        break;
    case 7:
        seven();
        break;
    case 8:
        eight();
        break;
    case 9:
        nine();
        break;
    case 14:
        forteen();
        break;
    case 15:
        fifteen();
        break;
    case 16:
        sixteen();
        break;
    default:
        break;
    }
}
static int left()
{
    int dirs[3] = { 3, 4, 5 };
    for (int i = 0; i < 3; i++) {
        if (dirs[i] == MOUSE_ANGLE)
            return 1;
    }
    return 0;
}
static void col_left()
{
    switch (MOUSE_ANGLE) {
    case 0:
        zero();
        break;
    case 1:
        one();
        break;
    case 2:
        three();
        break;
    case 6:
        six();
        break;
    case 7:
        seven();
        break;
    case 8:
        eight();
        break;
    case 9:
        nine();
        break;
    case 10:
        ten();
        break;
    case 11:
        eleven();
        break;
    case 12:
        twelve();
        break;
    case 13:
        thirteen();
        break;
    case 14:
        forteen();
        break;
    case 15:
        fifteen();
        break;
    case 16:
        sixteen();
        break;
    default:
        break;
    }
}
static char* _logic(void* obj)
{
    Direction* this = (Direction*)obj;
    if (!IN_ACTION && (KEY == W || KEY == S)) {
        if (KEY == W)
            HERO_SPEED = 2;
        if (KEY == S)
            HERO_SPEED = 4;
        /*
        if (COLLIDING && down()) {
            col_down();
        } else if (COLLIDING && up()) {
            col_up();
        } else if (COLLIDING && left()) {
            col_left();
        } else if (COLLIDING && right()) {
            col_right();
        } 
            */
        if (!COLLIDING) {

            switch (MOUSE_ANGLE) {
            case 0:
            case 16:
                Y -= HERO_SPEED;
                break;
            case 1:
                if (FRAMES_RENDERED % 2 == 0)
                    X += HERO_SPEED;
                Y -= HERO_SPEED;
                break;
            case 2:
                if (FRAMES_RENDERED % 1 == 0)
                    Y -= HERO_SPEED;
                X += HERO_SPEED;
                break;
            case 3:
                if (FRAMES_RENDERED % 2 == 0)
                    Y -= HERO_SPEED;
                X += HERO_SPEED;
                break;

            case 4:
                X += HERO_SPEED;
                break;
            case 5:
                if (FRAMES_RENDERED % 2 == 0)
                    Y += HERO_SPEED;
                X += HERO_SPEED;
                break;
            case 6:
                if (FRAMES_RENDERED % 1 == 0)
                    X += HERO_SPEED;
                Y += HERO_SPEED;
                break;
            case 7:
                if (FRAMES_RENDERED % 2 == 0)
                    X += HERO_SPEED;
                Y += HERO_SPEED;
                break;

            case 8:
                Y += HERO_SPEED;
                break;
            case 9:
                if (FRAMES_RENDERED % 2 == 0)
                    X -= HERO_SPEED;
                Y += HERO_SPEED;
                break;
            case 10:
                if (FRAMES_RENDERED % 1 == 0)
                    Y += HERO_SPEED;
                X -= HERO_SPEED;
                break;
            case 11:
                if (FRAMES_RENDERED % 2 == 0)
                    Y += HERO_SPEED;
                X -= HERO_SPEED;
                break;
            case 12:
                X -= HERO_SPEED;
                break;
            case 13:
                if (FRAMES_RENDERED % 2 == 0)
                    Y -= HERO_SPEED;
                X -= HERO_SPEED;
                break;
            case 14:
                if (FRAMES_RENDERED % 1 == 0)
                    X -= HERO_SPEED;
                Y -= HERO_SPEED;
                break;
            case 15:
                if (FRAMES_RENDERED % 2 == 0)
                    X -= HERO_SPEED;
                Y -= HERO_SPEED;
                break;

            default:
                break;
            }
        }
    }
    if (PRINT)
        printf("x: %d   y: %d    mouse: %d\n", X, Y);
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