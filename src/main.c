#include <SDL2/SDL.h>     /* SDL2 Library */
#include "Assets.h"       /* Add game assests to hastables */
#include "Atlas.h"        /* Font Atlas */
#include "Delta.h"        /* Timing */
#include "Floor.h"        /* Game Class */
#include "Graphics.h"     /* SDL2 graphics functions */
#include "Header.h"       /* Globals */
#include "Input.h"        /* Player Input */
#include "Logic_Table.h"  /* Hashtable of Logic_Nodes */
#include "Mouse.h"        /* ^..^ */
#include "Render_Table.h" /* Hashtable of Render_Nodes */
#include "Sprite.h"       /* Game Class*/

void DEFINE_GLOBALS();

int main(int argc, char** argv)
{
    char** state_logic;         /* State list for logic functions */
    char** state_render;        /* State list for render functions */
    SDL_Window* window;         /* The game window */
    SDL_Renderer* renderer;     /* The game renderer */
    Atlas* letters;             /* Font Atlas */
    Mouse* mouse;               /* Mouse Object */
    Render_Table* render_table; /* Hashtable of render functions */
    Logic_Table* logic_table;   /* Hashtable of logic functions */
    Table_Container container;  /* Container of hashtables */
    SDL_Thread* input_thread;   /* Thread that runs function input handler */

    SDL_init();

    DEFINE_GLOBALS();
    set_up_timer();

    window   = make_window("SDL2 Crawler");
    renderer = make_renderer(&window);

    set_render_options(renderer);

    letters      = CREATE_ATLAS();
    mouse        = CREATE_MOUSE(WINDOW_WIDTH);
    render_table = CREATE_RENDER_TABLE(TABLE_SIZE);
    logic_table  = CREATE_LOGIC_TABLE(TABLE_SIZE);
    input_thread = SDL_CreateThread(input_handler, "input_handler", NULL);
    container    = add_assets(logic_table, render_table, renderer);
    render_table = container.t_r;
    logic_table  = container.t_l;

    letters->map(letters, renderer);
    logic_table->print_table(logic_table);
    render_table->print_table(render_table);
    SDL_DetachThread(input_thread);

    while (!EXIT()) {
        start_timer();

        state_logic  = create_state(get_dark_forest_logic(), 5, state_logic);
        state_render = create_state(get_dark_forest_render(), 4, state_render);
        mouse->get_state(mouse);

        logic(logic_table, state_logic, 5);
        draw(render_table, state_render, renderer, 4);

        delay();
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

void DEFINE_GLOBALS()
{
    KEY           = NON;
    FULLSCREEN_ON = 0;
    KEY_STATE     = (Uint8*)SDL_GetKeyboardState(NULL);
    FPS           = 60;
    IN_ATTACK_ONE = 0;
    IN_ATTACK_TWO = 0;
}