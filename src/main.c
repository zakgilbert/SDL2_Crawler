
#include <SDL2/SDL.h> /* SDL2 Library */
#include <time.h>     /* Random Number Functions */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Assets.h"       
#include "Atlas.h"        
#include "Delta.h"        
#include "Graphics.h"     
#include "Header.h"       
#include "Input.h"        
#include "Logic_Table.h"  
#include "Render_Table.h" 
#include "Logic_Node.h"
#include "Render_Node.h"
#include "Mouse.h" /* ^..^ */
#include "Hero.h"

void DEFINE_GLOBALS();
int main(int argc, char** argv)
{
    char** state;               
    SDL_Window* window;         
    SDL_Renderer* renderer;     
                                
    Mouse* mouse;               
    Render_Table* render_table; 
    Logic_Table* logic_table;   
    Table_Container container;  
    SDL_Thread* input_thread;   

    SDL_init();
    srand(time(0));

    DEFINE_GLOBALS();
    set_up_timer();

    window   = make_window(argv[1]);
    renderer = make_renderer(&window);

    set_render_options(renderer);

    state = NULL;
    /**
        letters      = CREATE_ATLAS();
*/
    mouse        = CREATE_MOUSE(WINDOW_WIDTH);
    render_table = CREATE_RENDER_TABLE(TABLE_SIZE);
    logic_table  = CREATE_LOGIC_TABLE(TABLE_SIZE);
    input_thread = SDL_CreateThread(input_handler, "input_handler", NULL);
    container    = add_assets(logic_table, render_table, renderer);

    render_table = container.t_r;
    logic_table  = container.t_l;

    /**
    letters->map(letters, renderer);
    logic_table->print_table(logic_table);
    render_table->print_table(render_table);
*/
    SDL_DetachThread(input_thread);

    state = create_state(get_dark_forest_states(), NUM_STATES, state);

    while (!EXIT()) {
        start_timer();

        mouse->get_state(mouse);

        state = logic(logic_table, state, NUM_STATES);
        state = draw(render_table, state, renderer, NUM_STATES);

        delay();
        set_fullscreen(window);
        reset_timer();
    }

    /**
        letters->destroy(letters);
*/
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
    KEY             = NON;
    FULLSCREEN_ON   = 0;
    KEY_STATE       = (Uint8*)SDL_GetKeyboardState(&KEY_STATE_LEN);
    FPS             = 60;
    IN_ATTACK_ONE   = 0;
    IN_ATTACK_TWO   = 0;
    SECONDS_ELAPSED = 0;
    VAL_HERO        = 0;
    VAL_SNOW_X      = 450;
    VAL_SNOW_Y      = 450;
    HERO_SPEED      = 5;
    IN_ACTION       = 0;
    COLLIDING       = 0;
    COLLISION_INDEX = -1;
    OPEN_FOR_HIT    = 0;
    HIT_ANGLE       = -1;
}