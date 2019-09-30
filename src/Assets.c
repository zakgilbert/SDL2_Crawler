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
#include "Enemy.h"
#include "Hero.h"
#include "Collision.h"
#include "Rect_Node.h"

#define ASSETS_NUM 2
#define DARK_FOREST_STATES 3

static char* ASSET_STRINGS[] = {
    "map_directions",
    "graphics/map.png",
    "graphics/forest.png",
    "graphics/pally_1_edit.png",
    "graphics/pally_walk.png",
    "graphics/pally_run.png",
    "graphics/pally_attack_1.png",
    "graphics/pally_attack_2.png",
    "graphics/snow_stand.png",
    "graphics/snow_walk.png"
};
static char* STATE_STRINGS[] = {
    "map_directions",
    "graphics/map.png",
    "graphics/forest.png",
    "hero",
    "yeti",
    "col"
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
    int size    = 6;
    int* states = malloc(sizeof(int) * size);
    int temp[6] = {
        MAP_DIRECTIONS_KEY,
        FLOOR_FOREST_GROUND_KEY,
        FLOOR_FOREST_TREES_KEY,
        HERO_K,
        YETI_KEY,
        COLLISION_KEY
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

    Direction* directions = CREATE_DIRECTION(ASSET_STRINGS[0]);
    Floor* forest_floor   = CREATE_FLOOR(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, renderer, ASSET_STRINGS[1]);
    Floor* forest_trees   = CREATE_FLOOR(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, renderer, ASSET_STRINGS[2]);
    Hero* hero            = CREATE_HERO(STATE_STRINGS[HERO_K], 5);

    Sprite* hero_stand = CREATE_SPRITE(renderer, ASSET_STRINGS[3], 16, 16, hero_x, hero_y, 62, 80, MOVEMENT, HERO,
        ASSET_STRINGS[HERO_WALK_PATH],
        ASSET_STRINGS[HERO_STAND_PATH],
        ASSET_STRINGS[HERO_RUN_PATH],
        ASSET_STRINGS[HERO_ATTACK_1_PATH],
        ASSET_STRINGS[HERO_ATTACK_2_PATH]);

    Sprite* hero_walk = CREATE_SPRITE(renderer, ASSET_STRINGS[4], 10, 16, hero_x, hero_y, 104, 81, MOVEMENT, HERO,
        ASSET_STRINGS[HERO_WALK_PATH],
        ASSET_STRINGS[HERO_STAND_PATH],
        ASSET_STRINGS[HERO_RUN_PATH],
        ASSET_STRINGS[HERO_ATTACK_1_PATH],
        ASSET_STRINGS[HERO_ATTACK_2_PATH]);

    Sprite* hero_run = CREATE_SPRITE(renderer, ASSET_STRINGS[5], 8, 16, hero_x, hero_y, 94, 103, MOVEMENT, HERO,
        ASSET_STRINGS[HERO_WALK_PATH],
        ASSET_STRINGS[HERO_STAND_PATH],
        ASSET_STRINGS[HERO_RUN_PATH],
        ASSET_STRINGS[HERO_ATTACK_1_PATH],
        ASSET_STRINGS[HERO_ATTACK_2_PATH]);

    Sprite* hero_attack_1 = CREATE_SPRITE(renderer, ASSET_STRINGS[6], 15, 16, hero_x, hero_y, 180, 135, ACTION, HERO,
        ASSET_STRINGS[HERO_WALK_PATH],
        ASSET_STRINGS[HERO_STAND_PATH],
        ASSET_STRINGS[HERO_RUN_PATH],
        ASSET_STRINGS[HERO_ATTACK_1_PATH],
        ASSET_STRINGS[HERO_ATTACK_2_PATH]);

    Sprite* hero_attack_2 = CREATE_SPRITE(renderer, ASSET_STRINGS[7], 12, 16, hero_x, hero_y, 171, 123, ACTION, HERO,
        ASSET_STRINGS[HERO_WALK_PATH],
        ASSET_STRINGS[HERO_STAND_PATH],
        ASSET_STRINGS[HERO_RUN_PATH],
        ASSET_STRINGS[HERO_ATTACK_1_PATH],
        ASSET_STRINGS[HERO_ATTACK_2_PATH]);

    hero->add_sprite(hero, hero_stand, STAND_H);
    hero->add_sprite(hero, hero_walk, WALK_H);
    hero->add_sprite(hero, hero_run, RUN_H);
    hero->add_sprite(hero, hero_attack_1, ATTACK_ONE_H);
    hero->add_sprite(hero, hero_attack_2, ATTACK_TWO_H);

    Sprite* enemy_stand = CREATE_SPRITE(renderer, ASSET_STRINGS[8], 8, 8, snow_x, snow_y, 104, 109, MOVEMENT, ENEMY,
        ASSET_STRINGS[ENEMY_WALK_PATH], ASSET_STRINGS[ENEMY_STAND_PATH], NULL, NULL, NULL);

    Sprite* enemy_walk = CREATE_SPRITE(renderer, ASSET_STRINGS[9], 12, 8, snow_x, snow_y, 106, 120, MOVEMENT, ENEMY,
        ASSET_STRINGS[ENEMY_WALK_PATH], ASSET_STRINGS[ENEMY_STAND_PATH], NULL, NULL, NULL);

    Enemy* yeti = CREATE_ENEMY("yeti", 4, snow_x, snow_y);
    yeti->add_sprite(yeti, enemy_stand, STAND);
    yeti->add_sprite(yeti, enemy_walk, WALK);

    Collision* collision = CREATE_COLLISION(STATE_STRINGS[COLLISION_KEY], hero->col_rect);
    collision->add(collision, CREATE_RECT_NODE(yeti->col_rect));

    t_l->insert(t_l, CREATE_LOGIC_NODE(ASSET_STRINGS[0], directions, directions->logic, NULL));
    t_l->insert(t_l, CREATE_LOGIC_NODE(ASSET_STRINGS[1], forest_floor, forest_floor->logic, forest_floor->deallocate));
    t_l->insert(t_l, CREATE_LOGIC_NODE(ASSET_STRINGS[2], forest_trees, forest_trees->logic, forest_trees->deallocate));
    t_l->insert(t_l, CREATE_LOGIC_NODE(hero->key, hero, hero->logic, NULL));
    t_l->insert(t_l, CREATE_LOGIC_NODE(yeti->key, yeti, yeti->logic, NULL));
    t_l->insert(t_l, CREATE_LOGIC_NODE(collision->key, collision, collision->logic, NULL));

    t_r->insert(t_r, CREATE_RENDER_NODE(ASSET_STRINGS[0], directions, directions->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(ASSET_STRINGS[1], forest_floor, forest_floor->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(ASSET_STRINGS[2], forest_trees, forest_trees->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(hero->key, hero, hero->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(yeti->key, yeti, yeti->render));
    t_r->insert(t_r, CREATE_RENDER_NODE(collision->key, collision, collision->render));

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