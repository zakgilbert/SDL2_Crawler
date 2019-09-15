
#include "Input.h"
#include "Header.h"

int input_handler(void *data)
{

    while (SDL_WaitEvent(&ev) && !EXIT())
    {
        switch (ev.type)
        {
        case SDL_QUIT:
            key_state[O] = 1;
            break;

        case SDL_KEYDOWN:
            switch (ev.key.keysym.scancode)
            {
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
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            KEY = NON;
            switch (ev.key.keysym.scancode)
            {
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
    key_state[KEY] = 0;
    return 1;
}
int UP()
{
    return confirm(key_state[W]);
}
int LEFT()
{
    return confirm(key_state[A]);
}
int RIGHT()
{
    return confirm(key_state[D]);
}
int DOWN()
{
    return confirm(key_state[S]);
}
int CONFIRM()
{
    return confirm(key_state[J]);
}
int CANCEL()
{
    return confirm(key_state[L]);
}
int EXIT()
{
    return confirm(key_state[O]);
}
int FULL()
{
    return confirm(key_state[F]);
}
int NOTHING_PRESSED()
{
    return confirm(key_state[NON]);
}
void map_directions(void *obj)
{
    if (KEY == W)
    {
        switch (a2)
        {
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

    if (Y > 0)
        Y = 0;
    if (X > 0)
        X = 0;
    if (X < -2048 + WINDOW_WIDTH)
        X = -2048 + WINDOW_WIDTH;
    if (Y < -1792 + WINDOW_HEIGHT)
        Y = -1792 + WINDOW_HEIGHT;
}
