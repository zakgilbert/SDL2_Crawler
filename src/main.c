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
#include "Window_and_Renderer.h"
#include "Hash_l.h"
#include "Hash_r.h"
#include "Assets.h"
#include "Sprite.h"
#include "Mouse.h"

int main(int argc, char **argv)
{
    char **state_logic;
    char **state_render;
    FACING = down;
    KEY = NON;
    FULLSCREEN_ON = 0;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        return 1;
    }
    key_state = (Uint8 *)SDL_GetKeyboardState(NULL);
    FPS = 60;
    set_up_timer();

    struct SDL_Window *window = NULL;
    struct SDL_Renderer *renderer = NULL;
    window = make_window("win");
    renderer = make_renderer(&window);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    Atlas *letters = CREATE_ATLAS();
    Mouse *mouse = mouse_create(WINDOW_WIDTH);
    letters->map(letters, renderer);

    Hash_r *render_table = CREATE_HASH_R(TABLE_SIZE);
    Hash_l *logic_table = CREATE_HASH_L(TABLE_SIZE);

    struct Table_Container container = add_asset(logic_table, render_table, renderer);
    logic_table->print_table(logic_table);
    render_table->print_table(render_table);
    SDL_Thread *input_thread;

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
