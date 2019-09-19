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
#include "Direction.h"

#define ASSETS_NUM 2
#define DARK_FOREST_STATES 3

enum asset_enum {
    map_directions,
    floor_forest_ground,
    floor_forest_trees,
    hero,
    hero_walk,
    hero_attack_1,
    hero_attack_2,
    enemy_stand
};

static char* asset_strings[] = {
    "map_directions",
    "graphics/map.png",
    "graphics/forest.png",
    "graphics/pally_1_edit.png",
    "graphics/pally_walk.png",
    "graphics/pally_attack_1.png",
    "graphics/pally_attack_2.png",
    "graphics/snow_stand.png"
};

char** create_state(int* states, int num, char** state)
{
    if (NULL != state)
        free(state);
    state = NULL;
    state = malloc(sizeof(char*) * num);
    for (int i = 0; i < num; i++) {
        state[i] = malloc(100);
        state[i] = strcpy(state[i], asset_strings[states[i]]);
    }
    return state;
}

static int moving() { return ((KEY != NON) && (KEY == W)); }

int* get_dark_forest_logic()
{
    int size    = 5;
    int* states = malloc(sizeof(int) * size);
    int temp[5] = {
        map_directions,
        floor_forest_ground,
        floor_forest_trees,
        hero,
        enemy_stand
    };
    for (int i = 0; i < size; i++) {
        states[i] = temp[i];
    }

    return states;
}

int* get_dark_forest_render()
{
    int* states = malloc(sizeof(int) * 4);
    states[0]   = floor_forest_ground;
    states[1]   = floor_forest_trees;
    if (moving())
        states[2] = hero_walk;
    else if (IN_ATTACK_ONE)
        states[2] = hero_attack_1;
    else if (IN_ATTACK_TWO)
        states[2] = hero_attack_2;
    else
        states[2] = hero;
    states[3] = enemy_stand;
    return states;
}

Table_Container add_assets(Logic_Table* t_l, Render_Table* t_r, SDL_Renderer* renderer)
{
    Table_Container container;

    Direction* directions = CREATE_DIRECTION(asset_strings[0]);
    Floor* forest_floor   = CREATE_FLOOR(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, renderer, asset_strings[1]);
    Floor* forest_trees   = CREATE_FLOOR(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, renderer, asset_strings[2]);
    Sprite* hero          = CREATE_SPRITE(renderer, asset_strings[3], 16, 16, 0, 0, 62, 80, MOVEMENT, HERO);
    Sprite* hero_walk     = CREATE_SPRITE(renderer, asset_strings[4], 10, 16, 0, 0, 104, 81, MOVEMENT, HERO);
    Sprite* hero_attack_1 = CREATE_SPRITE(renderer, asset_strings[5], 15, 16, 0, 0, 180, 135, ACTION, HERO);
    Sprite* hero_attack_2 = CREATE_SPRITE(renderer, asset_strings[6], 12, 16, 0, 0, 171, 123, ACTION, HERO);
    Sprite* enemy_stand   = CREATE_SPRITE(renderer, asset_strings[7], 8, 8, 400, 400, 104, 109, MOVEMENT, ENEMY);

    t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings[0], directions, directions->logic));
    t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings[1], forest_floor, forest_floor->logic));
    t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings[2], forest_trees, forest_trees->logic));
    t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings[3], hero, hero->logic));
    t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings[4], hero_walk, hero_walk->logic));
    t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings[5], hero_attack_1, hero_attack_1->logic));
    t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings[6], hero_attack_2, hero_attack_2->logic));
    t_l->insert(t_l, CREATE_LOGIC_NODE(asset_strings[7], enemy_stand, enemy_stand->logic));

    t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings[0], directions, directions->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings[1], forest_floor, forest_floor->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings[2], forest_trees, forest_trees->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings[3], hero, hero->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings[4], hero_walk, hero_walk->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings[5], hero_attack_1, hero_attack_1->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings[6], hero_attack_2, hero_attack_2->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(asset_strings[7], enemy_stand, enemy_stand->render));

    container.t_l = t_l;
    container.t_r = t_r;

    return container;
}

char** draw(Render_Table* table, char** state, SDL_Renderer* renderer, int num)
{
    Render_Node* temp;
    SDL_RenderClear(renderer); /* Clear Canvas */
    for (int i = 0; i < num; i++) {
        temp = table->search(table, state[i]); /* Get render node */
        (*temp->funct)(temp->obj, renderer);   /* execute render function */
    }
    SDL_RenderPresent(renderer); /* draw to canvas */
    return state;
}

char** logic(Logic_Table* table, char** state, int num)
{
    Logic_Node* temp;
    for (int i = 0; i < num; i++) {
        temp = table->search(table, state[i]);
        (*temp->funct)(temp->obj);
    }
    return state;
}