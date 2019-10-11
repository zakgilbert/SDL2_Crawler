/**
 * Header.h contains all Globals and preprocessor definitions for SDL2_Crawler 
 */
#ifndef HEADER_H
#define HEADER_H

#define PRINT 1                  /* Set to 1 to print game data */
#define WINDOW_WIDTH 720         /* Width of window before fullscreen */
#define WINDOW_HEIGHT 576        /* Width of window before fullscreen */
#define MAP_W (WINDOW_WIDTH * 8) /* Width of map */
#define MAP_H (WINDOW_WIDTH * 8) /* Height of map */
#define PRIME_1 163              /* Prime numbers for seeding has tables */
#define PRIME_2 151              /* Prime numbers for seeding has tables */
#define TABLE_SIZE 500           /* Generic size for hash tables */
#define PI 3.14159               /* Ratio of a circle's circumference to its diameter */
#define NUM_STATES 5             /* Number of states in state q */
#define true 1                   /* true */
#define false 0                  /* false */

extern int FPS;             /* Frames per Second */
extern int FULLSCREEN_ON;   /* Fullscreen boolean */
extern int FRAMES_RENDERED; /* Counter for frames rendered every second */
extern int SECONDS_ELAPSED; /* Seconds in game */
extern int X;               /* Global X coordinate */
extern int Y;               /* Global Y coordinate */
extern int MOUSE_ANGLE;     /* Angle in degrees of from center of frame to mouse location */
extern int MOUSE_X;         /* Global mouse x coordinate */
extern int MOUSE_Y;         /* Global mouse y coordinate */
extern Uint8* KEY_STATE;    /* Array of key states */
extern int KEY_STATE_LEN;   /* Length of KEY_STATE array */
extern int IN_ATTACK_ONE;   /* Action Animation in progress */
extern int IN_ATTACK_TWO;   /* Action Animation in progress */
extern int VAL_HERO;        /* Starting position of hero */
extern int VAL_SNOW_X;      /* Position of snow x*/
extern int VAL_SNOW_Y;      /* Position of snow y*/
extern int HERO_SPEED;      /* Speed that hero moves at */
extern int IN_ACTION;       /* Is the hero acting */
extern int COLLIDING;       /* Is the hero colliding */
extern int COLLISION_INDEX; /* Index of collided object */
extern int HERO_WIDTH;      /* Index of collided object */
extern int HERO_HEIGHT;     /* Index of collided object */
extern int OPEN_FOR_HIT;    /* If an enemy has an opportunity to strike Hero */
extern int HIT_ANGLE;       /* Angle between enemy and hero or -1 if OPEN_FOR_HIT is false */

int FPS;
int FULLSCREEN_ON;
int FRAMES_RENDERED;
int SECONDS_ELAPSED;
int X;
int Y;
int MOUSE_ANGLE;
int MOUSE_X;
int MOUSE_Y;
Uint8* KEY_STATE;
int KEY_STATE_LEN;
int IN_ATTACK_ONE;
int IN_ATTACK_TWO;
int VAL_HERO;
int VAL_SNOW_X;
int VAL_SNOW_Y;
int HERO_SPEED;
int IN_ACTION;
int COLLIDING;
int COLLISION_INDEX;
int HERO_WIDTH;
int HERO_HEIGHT;
int OPEN_FOR_HIT;
int HIT_ANGLE;

/**
 * Enum values can be referenced as follows...
 *  - if(KEY == S)
 *  - if(KEY_VALUE[S])
 */
enum KEYS {
    S   = SDL_SCANCODE_S,
    W   = SDL_SCANCODE_W,
    A   = SDL_SCANCODE_A,
    D   = SDL_SCANCODE_D,
    J   = SDL_SCANCODE_J,
    L   = SDL_SCANCODE_L,
    O   = SDL_SCANCODE_O,
    F   = SDL_SCANCODE_F,
    R   = SDL_SCANCODE_R,
    NON = 0
} KEY;

enum SPRITE_STATE_TYPES {
    MOVEMENT,
    ACTION
};
enum SPRITE_TYPES {
    HERO,
    ENEMY
};

enum ASSET_PATH_ENUM {
    MAP_DIRECTIONS_PATH,
    HERO_STAND_PATH,
    HERO_WALK_PATH,
    HERO_RUN_PATH,
    HERO_ATTACK_1_PATH,
    HERO_ATTACK_2_PATH,
    HERO_READY_STAND_PATH,
    HERO_READY_WALK_PATH,
    HERO_TAKES_DAMAGE,
    ENEMY_STAND_PATH,
    ENEMY_WALK_PATH,
    TERRAIN_PATH,
    ENEMY_ATK_1_PATH
};
enum ASSET_KEYS_ENUM {
    COLLISION_KEY,
    MAP_DIRECTIONS_KEY,
    TERRAIN_KEY,
    HERO_K,
    YETI_KEY
};

enum HERO_STATES {
    STAND_H,
    WALK_H,
    RUN_H,
    ATTACK_ONE_H,
    ATTACK_TWO_H,
    STAND_RDY_H,
    WALK_RDY_H,
    DAMAGE_H
};
enum ENEMY_STATES {
    STAND,
    WALK,
    ATTACK
};

#endif /* HEADER_H */