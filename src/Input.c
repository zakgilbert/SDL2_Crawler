#include <SDL2/SDL.h>
#include "Header.h"
#include "Input.h"

int input_handler(void* data)
{
    union SDL_Event ev; /*union for SDL event */

    while (SDL_WaitEvent(&ev) && !EXIT()) {
        switch (ev.type) {
        case SDL_QUIT:
            KEY_STATE[O] = 1;
            break;

        case SDL_KEYDOWN:
            switch (ev.key.keysym.scancode) {
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                KEY = S;
                continue;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                KEY = W;
                continue;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                IN_ATTACK_ONE = 1;
                KEY           = A;
                continue;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                IN_ATTACK_TWO = 1;
                KEY           = D;
                continue;
            case SDL_SCANCODE_J:
                KEY = J;
                continue;
            case SDL_SCANCODE_L:
                KEY = L;
                continue;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            KEY = NON;
            switch (ev.key.keysym.scancode) {
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                continue;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                continue;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                continue;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                continue;
            case SDL_SCANCODE_J:
                continue;
            case SDL_SCANCODE_L:
                continue;
            case SDL_SCANCODE_F:
                FULLSCREEN_ON = !(FULLSCREEN_ON);
                continue;
            default:
                break;
            }
        default:
            break;
        }
    }
    return 0;
}

int confirm(int val)
{
    if (!val)
        return 0;
    KEY_STATE[KEY] = 0;
    return 1;
}

int UP() { return confirm(KEY_STATE[W]); }
int LEFT() { return confirm(KEY_STATE[A]); }
int RIGHT() { return confirm(KEY_STATE[D]); }
int DOWN() { return confirm(KEY_STATE[S]); }
int CONFIRM() { return confirm(KEY_STATE[J]); }
int CANCEL() { return confirm(KEY_STATE[L]); }
int EXIT() { return confirm(KEY_STATE[O]); }
int FULL() { return confirm(KEY_STATE[F]); }
int NOTHING_PRESSED() { return confirm(KEY_STATE[NON]); }

void map_directions(void* obj)
{
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
