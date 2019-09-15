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
#include "Logic_Table.h"
#include "Render_Table.h"
#include "Assets.h"
#include "Sprite.h"
#include "Mouse.h"

static void DEFINE_GLOBALS()
{
    KEY = NON;
    FULLSCREEN_ON = 0;
    KEY_STATE = (Uint8 *)SDL_GetKeyboardState(NULL);
    FPS = 60;
}

int main(int argc, char **argv)
{
    char **state_logic;               /* State list for logic functions */
    char **state_render;              /* State list for render functions */
    struct Table_Container container; /* Container of hashtables */
    struct SDL_Window *window;        /* The game window */
    struct SDL_Renderer *renderer;    /* The game renderer */
    Atlas *letters;                   /* Font Atlas */
    Mouse *mouse;                     /* Mouse Object */
    Render_Table *render_table;       /* Hashtable of render functions */
    Logic_Table *logic_table;         /* Hashtable of logic functions */
    SDL_Thread *input_thread;         /* Thread that runs function input handler */

    SDL_init();

    DEFINE_GLOBALS();
    set_up_timer();

    window = make_window("SDL2 Crawler");
    renderer = make_renderer(&window);

    set_render_options(renderer);

    letters = CREATE_ATLAS();
    mouse = CREATE_MOUSE(WINDOW_WIDTH);
    render_table = CREATE_RENDER_TABLE(TABLE_SIZE);
    logic_table = CREATE_LOGIC_TABLE(TABLE_SIZE);
    input_thread = SDL_CreateThread(input_handler, "input_handler", NULL);
    container = add_assets(logic_table, render_table, renderer);
    render_table = container.t_r;
    logic_table = container.t_l;

    letters->map(letters, renderer);
    logic_table->print_table(logic_table);
    render_table->print_table(render_table);
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
    mouse->destroy(mouse);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
