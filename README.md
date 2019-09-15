# SDL2_Crawler
## Description
This is a new type of dungeon crawler...
## How to Contribute
### Game States
A game is defined by it's states, thus the best way to contribute would be to implement more states.
Every state is represented by an array of strings and a corresponding enum and is defined as follows...
```c
/* from Assets.c */
static char *asset_strings_f[] =
{
    "map_directions",
    "graphics/map.png",
    "graphics/forest.png",
    "graphics/pally_1_edit.png",
    "graphics/pally_walk.png"
};

enum asset_enum
{
    map_directions_e,
    floor_forest_ground,
    floor_forest_trees,
    hero,
    hero_walk
};

```
Each member of these lists represents an action that needs to be performed in order to achieve the goals of the states. Every action corresponds to a game class such as Floor.

```c
#ifndef JRPG_FLOOR_H
#define JRPG_FLOOR_H

/**
 * Holds an SDL Texture that resembles the ground in SDL2_Crawler,
 * see map and forest in main.c
*/
typedef struct _Floor
{
    void (*destroy)(struct _Floor *);                  /* Free Allocated Memory */
    void (*render)(void *obj, SDL_Renderer *renderer); /* Render function */
    void (*logic)(void *obj);                          /* Logic function */

    SDL_Texture *texture; /* SDL Texture */
    SDL_Rect rect;        /* SDL Rectangle */
} Floor;

Floor *CREATE_FLOOR(int x, int y, int w, int h, SDL_Renderer *renderer, const char *path);
```
Every game class object contains two important functions `render` and `logic`. In `main.c` we define two hash tables...
```c
Hash_r *render_table; /* Hashtable of render functions */
Hash_l *logic_table;  /* Hashtable of logic functions */
```
As well as corresponding game state lists...
```c
char **state_logic;  /* State list for logic functions */
char **state_render; /* State list for render functions */
```
The appearance that is generated and the logic that is performed varies from state to state. One thing that states have in common is that they all render graphics and they all perform game logic, thus We have two hash tables that contain all the possible rendering and logical actions.  A state is executed when the string array of a state is passed into the draw or logic functions...
```c
/* game loop in main.c */
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
```
Hence the elements in `state_logic` and `state_render` are keys in the hash table. We execute logic and render functions as we iterate through the arrays...
```c
/* draw defined in Assets.c */
void draw(Hash_r *table, char **state, SDL_Renderer *renderer, int num)
{
    Render_Node *temp;
    SDL_RenderClear(renderer); /* Clear Canvas */
    for (int i = 0; i < num; i++)
    {
        temp = table->search(table, state[i]); /* Get render node */
        (*temp->funct)(temp->obj, renderer);   /* execute render function */
    }
    SDL_RenderPresent(renderer); /* draw to canvas */
}
```
Game Classes are added to a hash table as follows ...
```c
/* Instantiate a floor object */
Floor *floor = CREATE_FLOOR(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, renderer, asset_strings[i]);
/* Insert a logic node */
t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings[i], floor, floor->logic));
/* Insert a render node */
t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings[i], floor, floor->render));
```
A node is defined as follows
```c
#ifndef RENDER_NODE_H
#define RENDER_NODE_H

typedef struct SDL_Renderer SDL_Renderer;
typedef void render_function(void *obj, SDL_Renderer *renderer);

/**
 * A node type that holds the data needed to pull the render function from
 * the Hash_r
 */
typedef struct _Render_Node
{
    void (*destroy)(struct _Render_Node *this);      /* Free allocated memory */
    void (*print)(struct _Render_Node *this, int i); /* Print node data */

    void *obj;               /* Pointer to object whose render function will be called */
    render_function(*funct); /* Render function be called */
    int index;               /* Index the node is stored at */
    char *key;               /* Key of node */
} Render_Node;
Render_Node *CREATE_RENDER_NODE(char *key, void *obj, render_function funct);

#endif /* RENDER_NODE_H */
```
