
/**
*  Assets.c
*/

#include <SDL2/SDL.h>

#include "Assets.h"
#include "Floor.h"
#include "Header.h"
#include "Input.h"
#include "Logic_Node.h"
#include "Logic_Table.h"
#include "Render_Node.h"
#include "Render_Table.h"
#include "Sprite.h"

#define ASSETS_NUM 2
#define DARK_FOREST_STATES 3

enum asset_enum {
    map_directions_e,
    floor_forest_ground,
    floor_forest_trees,
    hero,
    hero_walk
};

static char* asset_strings[] = {
    "graphics/map.png",
    "graphics/forest.png"
};

static char* asset_strings_f[] = {
    "map_directions",
    "graphics/map.png",
    "graphics/forest.png",
    "graphics/pally_1_edit.png",
    "graphics/pally_walk.png"
};

char** create_state(int* states, int num, char** state)
{
    if (NULL != state)
        free(state);
    state = NULL;
    state = malloc(sizeof(char*) * num);
    for (int i = 0; i < num; i++) {
        state[i] = malloc(strlen(asset_strings_f[states[i]]));
        state[i] = strcpy(state[i], asset_strings_f[states[i]]);
    }
    return state;
}

static int moving() { return ((KEY != NON) && (KEY == W)); }

int* get_dark_forest_logic()
{
    int* states = malloc(sizeof(int) * 4);
    states[2] = floor_forest_ground;
    states[1] = floor_forest_trees;
    states[0] = map_directions_e;
    if (moving())
        states[3] = hero_walk;
    else
        states[3] = hero;

    return states;
}

int* get_dark_forest_render()
{
    int* states = malloc(sizeof(int) * 3);
    states[0] = floor_forest_ground;
    states[1] = floor_forest_trees;
    if (moving())
        states[2] = hero_walk;
    else
        states[2] = hero;
    return states;
}

Table_Container add_assets(Logic_Table* t_l, Render_Table* t_r, SDL_Renderer* renderer)
{
    for (int i = 0; i < ASSETS_NUM; i++) {
        Floor* floor = CREATE_FLOOR(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, renderer, asset_strings[i]);
        t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings[i], floor, floor->logic));
        t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings[i], floor, floor->render));
    }
    t_l->insert(t_l, CREATE_LOGIC_NODE("map_directions", NULL, map_directions));

    Sprite* hero = CREATE_SPRITE(renderer, asset_strings_f[3], 16, 16, 62, 80, 0);
    t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings_f[3], hero, hero->logic));
    t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings_f[3], hero, hero->render));

    Sprite* hero_walk = CREATE_SPRITE(renderer, asset_strings_f[4], 10, 16, 104, 81, 1);
    t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings_f[4], hero_walk, hero_walk->logic));
    t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings_f[4], hero_walk, hero_walk->render));
    Table_Container containter = { t_l, t_r };
    return containter;
}

void draw(Render_Table* table, char** state, SDL_Renderer* renderer, int num)
{
    Render_Node* temp;
    SDL_RenderClear(renderer); /* Clear Canvas */
    for (int i = 0; i < num; i++) {
        temp = table->search(table, state[i]); /* Get render node */
        (*temp->funct)(temp->obj, renderer); /* execute render function */
    }
    SDL_RenderPresent(renderer); /* draw to canvas */
}

void logic(Logic_Table* table, char** state, int num)
{
    Logic_Node* temp;
    for (int i = 0; i < num; i++) {
        temp = table->search(table, state[i]);
        (*temp->funct)(temp->obj);
    }
}