
/**
*  Direction.c
*/

#include <SDL2/SDL.h>
#include "Direction.h"
#include "Header.h"
#include "Calc.h"

static void print(Direction* this)
{
    printf("%p", this);
}
static void _destroy(Direction* this)
{
    if (NULL != this) {
        if (PRINT) {
            printf("%p\n", this);
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
static char* _logic(void* obj)
{
    Direction* this = (Direction*)obj;
    if (COLLIDING && OPEN_FOR_HIT && HIT_ANGLE != -1) {
        (*this->hit_functions[HIT_ANGLE])(20, 20);
        OPEN_FOR_HIT = 0;
        HIT_ANGLE    = -1;
    }
    if (!IN_ACTION && (WALK_F(false) || RUN_F(false))) {
        if (KEY == W)
            HERO_SPEED = 2;
        if (KEY == S)
            HERO_SPEED = 4;
        (*this->move_functions[MOUSE_ANGLE])(HERO_SPEED, HERO_SPEED);
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

    this->hit_functions[0] = hit_down;
    this->hit_functions[1] = hit_down_left;
    this->hit_functions[2] = hit_left;
    this->hit_functions[3] = hit_up_left;
    this->hit_functions[4] = hit_up;
    this->hit_functions[5] = hit_up_right;
    this->hit_functions[6] = hit_right;
    this->hit_functions[7] = hit_down_right;

    this->move_functions[0]  = move_down;
    this->move_functions[1]  = move_down_down_left;
    this->move_functions[2]  = move_down_left;
    this->move_functions[3]  = move_down_left_left;
    this->move_functions[4]  = move_left;
    this->move_functions[5]  = move_up_left_left;
    this->move_functions[6]  = move_up_left;
    this->move_functions[7]  = move_up_up_left;
    this->move_functions[8]  = move_up;
    this->move_functions[9]  = move_up_up_right;
    this->move_functions[10] = move_up_right;
    this->move_functions[11] = move_up_right_right;
    this->move_functions[12] = move_right;
    this->move_functions[13] = move_down_right_right;
    this->move_functions[14] = move_down_right;
    this->move_functions[15] = move_down_down_right;
    this->move_functions[16] = move_down;

    this->key = key;

    if (PRINT)
        printf("%p\n", this);
    return this;
}

static int confirm(int val)
{
    if (!val)
        return 0;
    KEY_STATE[KEY] = 0;
    return 1;
}

int WALK_F(int close)
{
    if (close)
        return confirm(KEY_STATE[W]);
    return (KEY_STATE[W]);
}
int ATTACK_1_F(int close)
{
    if (close)
        return confirm(KEY_STATE[A]);
    return (KEY_STATE[A]);
}
int ATTACK_2_F(int close)
{
    if (close)
        return confirm(KEY_STATE[D]);
    return (KEY_STATE[D]);
}
int RUN_F(int close)
{
    if (close)
        return confirm(KEY_STATE[S]);
    return (KEY_STATE[S]);
}
int STANCE_F(int close) { return (close) ? confirm(KEY_STATE[R]) : KEY_STATE[R]; }
int CONFIRM(int close)
{
    if (close)
        return confirm(KEY_STATE[J]);
    return (KEY_STATE[J]);
}
int CANCEL(int close)
{
    if (close)
        return confirm(KEY_STATE[L]);
    return (KEY_STATE[L]);
}
int FULL(int close)
{
    if (close)
        return confirm(KEY_STATE[F]);
    return (KEY_STATE[F]);
}
int NOTHING_PRESSED(int close)
{
    if (close)
        return confirm(KEY_STATE[NON]);
    return (KEY_STATE[NON]);
}
void move_down(int x, int y)
{
    Y -= y;
}
void move_down_down_left(int x, int y)
{
    if (FRAMES_RENDERED % 2 == 0)
        X += x;
    Y -= y;
}
void move_down_left(int x, int y)
{
    if (FRAMES_RENDERED % 1 == 0)
        Y -= y;
    X += x;
}
void move_down_left_left(int x, int y)
{
    if (FRAMES_RENDERED % 2 == 0)
        Y -= y;
    X += x;
}
void move_left(int x, int y)
{
    X += x;
}
void move_up_left_left(int x, int y)
{
    if (FRAMES_RENDERED % 2 == 0)
        Y += y;
    X += x;
}
void move_up_left(int x, int y)
{
    if (FRAMES_RENDERED % 1 == 0)
        X += x;
    Y += y;
}
void move_up_up_left(int x, int y)
{
    if (FRAMES_RENDERED % 2 == 0)
        X += x;
    Y += y;
}
void move_up(int x, int y)
{
    Y += y;
}
void move_up_up_right(int x, int y)
{
    if (FRAMES_RENDERED % 2 == 0)
        X -= x;
    Y += y;
}
void move_up_right(int x, int y)
{
    if (FRAMES_RENDERED % 1 == 0)
        Y += y;
    X -= x;
}
void move_up_right_right(int x, int y)
{
    if (FRAMES_RENDERED % 2 == 0)
        Y += y;
    X -= x;
}
void move_right(int x, int y)
{
    X -= x;
}
void move_down_right_right(int x, int y)
{
    if (FRAMES_RENDERED % 2 == 0)
        Y -= y;
    X -= x;
}
void move_down_right(int x, int y)
{
    if (FRAMES_RENDERED % 1 == 0)
        X -= x;
    Y -= y;
}
void move_down_down_right(int x, int y)
{
    if (FRAMES_RENDERED % 2 == 0)
        X -= x;
    Y -= y;
}
void hit_down(int x, int y)
{
    Y -= y;
}
void hit_down_left(int x, int y)
{
    X += x;
    Y -= y;
}
void hit_left(int x, int y)
{
    X += x;
}
void hit_up_left(int x, int y)
{
    X += x;
    Y += y;
}
void hit_up(int x, int y)
{
    Y += y;
}
void hit_up_right(int x, int y)
{
    X -= x;
    Y += y;
}
void hit_right(int x, int y)
{
    X -= x;
}
void hit_down_right(int x, int y)
{
    X -= x;
    Y -= y;
}