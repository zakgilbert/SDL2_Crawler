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
                KEY = A;
                continue;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                KEY = D;
                continue;
            case SDL_SCANCODE_J:
                KEY = J;
                continue;
            case SDL_SCANCODE_L:
                KEY = L;
                continue;
            case SDL_SCANCODE_R:
                KEY = R;
                continue;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (ev.key.keysym.scancode) {
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                KEY = NON;
                continue;
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                KEY = NON;
                continue;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                KEY = NON;
                continue;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                KEY = NON;
                continue;
            case SDL_SCANCODE_J:
                KEY = NON;
                continue;
            case SDL_SCANCODE_L:
                KEY = NON;
                continue;
            case SDL_SCANCODE_F:
                KEY           = NON;
                FULLSCREEN_ON = !(FULLSCREEN_ON);
                continue;
            case SDL_SCANCODE_R:
                KEY = NON;
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

int EXIT()
{
    return (KEY_STATE[O]);
}