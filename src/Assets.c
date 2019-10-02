#include <SDL2/SDL.h>
#include "Assets.h"
#include "Header.h"
#include "Input.h"
#include "Logic_Node.h"
#include "Logic_Table.h"
#include "Render_Node.h"
#include "Render_Table.h"
#include "Sprite.h"
#include "Direction.h"
#include "Enemy.h"
#include "Hero.h"
#include "Collision.h"
#include "Rect_Node.h"
#include "Terrain.h" /* Hold tile textures for map graphics */

#define ASSETS_NUM 2
#define DARK_FOREST_STATES 3

static char* ASSET_STRINGS[] = {
    "map_directions",
    "graphics/pally_1_edit.png",
    "graphics/pally_walk.png",
    "graphics/pally_run.png",
    "graphics/pally_attack_1.png",
    "graphics/pally_attack_2.png",
    "graphics/snow_stand.png",
    "graphics/snow_walk.png",
    "graphics/dungeon_floor.png",
    "graphics/snow_atk_1.png"
};
static char* STATE_STRINGS[] = {
    "col",
    "map_directions",
    "terrain",
    "hero",
    "yeti"
};

char** create_state(int* states, int num, char** state)
{
    if (NULL != state)
        free(state);
    state = NULL;
    state = malloc(sizeof(char*) * num);
    for (int i = 0; i < num; i++) {
        state[i] = malloc(100);
        state[i] = strcpy(state[i], STATE_STRINGS[states[i]]);
    }
    return state;
}

static int moving() { return ((KEY != NON) && (KEY == W)); }

int* get_dark_forest_states()
{
    int size             = NUM_STATES;
    int* states          = malloc(sizeof(int) * size);
    int temp[NUM_STATES] = {
        COLLISION_KEY,
        MAP_DIRECTIONS_KEY,
        TERRAIN_KEY,
        HERO_K,
        YETI_KEY
    };
    for (int i = 0; i < size; i++) {
        states[i] = temp[i];
    }

    return states;
}

Table_Container add_assets(Logic_Table* t_l, Render_Table* t_r, SDL_Renderer* renderer)
{
    Table_Container container;

    int* hero_x;
    int* hero_y;
    int* snow_x;
    int* snow_y;
    hero_x = &VAL_HERO;
    hero_y = &VAL_HERO;
    snow_x = &VAL_SNOW_X;
    snow_y = &VAL_SNOW_Y;

    Terrain* terrain      = CREATE_TERRAIN(ASSET_STRINGS[TERRAIN_PATH], STATE_STRINGS[TERRAIN_KEY], renderer, 0, 0, WINDOW_WIDTH * 2, WINDOW_WIDTH * 4, 160, 80, 4, 5);
    Direction* directions = CREATE_DIRECTION(ASSET_STRINGS[MAP_DIRECTIONS_PATH]);
    Hero* hero            = CREATE_HERO(STATE_STRINGS[HERO_K], 5);

    Sprite* hero_stand    = CREATE_SPRITE(renderer, ASSET_STRINGS[HERO_STAND_PATH], 16, 16, hero_x, hero_y, 62, 80, MOVEMENT, HERO);
    Sprite* hero_walk     = CREATE_SPRITE(renderer, ASSET_STRINGS[HERO_WALK_PATH], 10, 16, hero_x, hero_y, 104, 81, MOVEMENT, HERO);
    Sprite* hero_run      = CREATE_SPRITE(renderer, ASSET_STRINGS[HERO_RUN_PATH], 8, 16, hero_x, hero_y, 94, 103, MOVEMENT, HERO);
    Sprite* hero_attack_1 = CREATE_SPRITE(renderer, ASSET_STRINGS[HERO_ATTACK_1_PATH], 15, 16, hero_x, hero_y, 180, 135, ACTION, HERO);
    Sprite* hero_attack_2 = CREATE_SPRITE(renderer, ASSET_STRINGS[HERO_ATTACK_2_PATH], 12, 16, hero_x, hero_y, 171, 123, ACTION, HERO);

    hero->add_sprite(hero, hero_stand, STAND_H);
    hero->add_sprite(hero, hero_walk, WALK_H);
    hero->add_sprite(hero, hero_run, RUN_H);
    hero->add_sprite(hero, hero_attack_1, ATTACK_ONE_H);
    hero->add_sprite(hero, hero_attack_2, ATTACK_TWO_H);

    Sprite* enemy_stand = CREATE_SPRITE(renderer, ASSET_STRINGS[ENEMY_STAND_PATH], 8, 8, snow_x, snow_y, 104, 109, MOVEMENT, ENEMY);
    Sprite* enemy_walk  = CREATE_SPRITE(renderer, ASSET_STRINGS[ENEMY_WALK_PATH], 12, 8, snow_x, snow_y, 106, 120, MOVEMENT, ENEMY);
    Sprite* enemy_atk_1 = CREATE_SPRITE(renderer, ASSET_STRINGS[ENEMY_ATK_1_PATH], 12, 8, snow_x, snow_y, 217, 120, ACTION, ENEMY);

    Enemy* yeti = CREATE_ENEMY("yeti", 3, snow_x, snow_y);
    yeti->add_sprite(yeti, enemy_stand, STAND);
    yeti->add_sprite(yeti, enemy_walk, WALK);
    yeti->add_sprite(yeti, enemy_atk_1, ATTACK);

    Collision* collision = CREATE_COLLISION(STATE_STRINGS[COLLISION_KEY], &hero->col_rect);
    collision->add(collision, CREATE_RECT_NODE(&yeti->col_rect));

    t_l->insert(t_l, CREATE_LOGIC_NODE(ASSET_STRINGS[MAP_DIRECTIONS_PATH], directions, directions->logic, NULL));
    t_l->insert(t_l, CREATE_LOGIC_NODE(hero->key, hero, hero->logic, NULL));
    t_l->insert(t_l, CREATE_LOGIC_NODE(yeti->key, yeti, yeti->logic, NULL));
    t_l->insert(t_l, CREATE_LOGIC_NODE(collision->key, collision, collision->logic, NULL));
    t_l->insert(t_l, CREATE_LOGIC_NODE(terrain->key, terrain, terrain->logic, NULL));

    t_r->insert(t_r, CREATE_RENDER_NODE(ASSET_STRINGS[MAP_DIRECTIONS_PATH], directions, directions->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(hero->key, hero, hero->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(yeti->key, yeti, yeti->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(collision->key, collision, collision->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(terrain->key, terrain, terrain->render));

    container.t_l = t_l;
    container.t_r = t_r;

    return container;
}

char** draw(Render_Table* table, char** state, SDL_Renderer* renderer, int num)
{
    Render_Node* temp;
    SDL_RenderClear(renderer);
    for (int i = 0; i < num; i++) {
        temp     = table->search(table, state[i]);
        state[i] = strcpy(state[i], (*temp->funct)(temp->obj, renderer));
    }
    SDL_RenderPresent(renderer);
    return state;
}

char** logic(Logic_Table* table, char** state, int num)
{
    Logic_Node* temp;
    for (int i = 0; i < num; i++) {
        temp     = table->search(table, state[i]);
        state[i] = strcpy(state[i], (*temp->funct)(temp->obj));
    }
    return state;
}