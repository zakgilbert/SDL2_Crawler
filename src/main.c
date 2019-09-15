#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_thread.h>

#include "Header.h"
#include "Floor.h"
#include "Atlas.h"
#include "Input.h"
#include "Delta.h"
#include "Graphics.h"
#include "Hash_l.h"
#include "Hash_r.h"
#include "Assets.h"
#include "Sprite.h"
#include "Mouse.h"

int main(int argc, char **argv)
{
    char **state_logic;               /* State list for logic functions */
    char **state_render;              /* State list for render functions */
    struct Table_Container container; /* Container of hashtables */
    struct SDL_Window *window;        /* The game window */
    struct SDL_Renderer *renderer;    /* The game renderer */
    Atlas *letters;                   /* Font Atlas */
    Mouse *mouse;                     /* Mouse Object */
    Hash_r *render_table;             /* Hashtable of render functions */
    Hash_l *logic_table;              /* Hashtable of logic functions */
    SDL_Thread *input_thread;         /* Thread that runs function input handler */

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        return 1;
    }

    DEFINE_GLOBALS();
    set_up_timer();

    window = NULL;
    renderer = NULL;
    window = make_window("win");
    renderer = make_renderer(&window);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    letters = CREATE_ATLAS();
    letters->map(letters, renderer);
    mouse = mouse_create(WINDOW_WIDTH);

    render_table = CREATE_HASH_R(TABLE_SIZE);
    logic_table = CREATE_HASH_L(TABLE_SIZE);

    container = add_assets(logic_table, render_table, renderer);

    logic_table->print_table(logic_table);
    render_table->print_table(render_table);

    input_thread = SDL_CreateThread(input_handler, "input_handler", NULL);
    SDL_DetachThread(input_thread);

    while (!EXIT())
    {
        start_timer();

        state_logic = create_state(get_dark_forest_logic(), 4, state_logic);
        state_render = create_state(get_dark_forest_render(), 3, state_render);
        mouse->get_state(mouse);

        logic(logic_table, state_logic, 4);
        draw(render_table, state_render, renderer, 3);

        FRAMES_RENDERED = delay();
        set_fullscreen(window);
        reset_timer();
    }
    letters->destroy(letters);
    logic_table->destroy(logic_table);
    render_table->destroy(render_table);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

void DEFINE_GLOBALS()
{
    KEY = NON;
    FULLSCREEN_ON = 0;
    KEY_STATE = (Uint8 *)SDL_GetKeyboardState(NULL);
    FPS = 60;
}
