/**
 * Header.h contains all Globals and preprocessor definitions for SDL2_Crawler 
 */
#ifndef JRPG_HEADER_H
#define JRPG_HEADER_H

#define PRINT 0           /* Set to 1 to print game data */
#define WINDOW_WIDTH 720  /* Width of window before fullscreen */
#define WINDOW_HEIGHT 576 /* Width of window before fullscreen */
#define PRIME_1 163       /* Prime numbers for seeding has tables */
#define PRIME_2 151       /* Prime numbers for seeding has tables */
#define TABLE_SIZE 500    /* Generic size for hash tables */
#define PI 3.14159        /* Ratio of a circle's circumference to its diameter */

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
extern int IN_ATTACK_ONE;   /* Action Animation in progress */
extern int IN_ATTACK_TWO;   /* Action Animation in progress */
extern int VAL_HERO;        /* Starting position of hero */
extern int VAL_SNOW_X;      /* Position of snow x*/
extern int VAL_SNOW_Y;      /* Position of snow y*/
extern int HERO_SPEED;      /*Speed that hero moves at */

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
int IN_ATTACK_ONE;
int IN_ATTACK_TWO;
int VAL_HERO;
int VAL_SNOW_X;
int VAL_SNOW_Y;
int HERO_SPEED;

/**
 * Enum values can be referenced as follows...
 *  - if(KEY == S)
 *  - if(KEY_VALUE[S])
 */
enum KEYS {
    S = SDL_SCANCODE_S,
    W = SDL_SCANCODE_W,
    A = SDL_SCANCODE_A,
    D = SDL_SCANCODE_D,
    J = SDL_SCANCODE_J,
    L = SDL_SCANCODE_L,
    O = SDL_SCANCODE_O,
    F = SDL_SCANCODE_F,
    NON
} KEY;

enum SPRITE_STATE_TYPES {
    MOVEMENT,
    ACTION
};
enum SPRITE_TYPES {
    HERO,
    ENEMY
};

enum ASSET_ENUM {
    MAP_DIRECTIONS,
    FLOOR_FOREST_GROUND,
    FLOOR_FOREST_TREES,
    HERO_STAND,
    HERO_WALK,
    HERO_RUN,
    HERO_ATTACK_1,
    HERO_ATTACK_2,
    ENEMY_STAND,
    ENEMY_WALK
};

#endif