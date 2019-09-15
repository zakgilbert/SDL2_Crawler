#ifndef JRPG_HEADER_H
#define JRPG_HEADER_H

#define PRINT 1

#define WINDOW_WIDTH (356)
#define WINDOW_HEIGHT (324)
#define PRIME_1 (163)
#define PRIME_2 (151)

#define TABLE_SIZE 500

#define SPEED 5

extern int FPS;
int FPS;

extern int FULLSCREEN_ON;
int FULLSCREEN_ON;

extern int FRAMES_RENDERED;
int FRAMES_RENDERED;

extern int MOVEMENT_DISABLED;
int MOVEMENT_DISABLED;

extern int X;
int X;

extern int Y;
int Y;

extern int a2;
int a2;

extern int MOUSE_X;
int MOUSE_X;

extern int MOUSE_Y;
int MOUSE_Y;
enum DIRECTIONS
{
    down,
    up,
    left,
    right
} FACING,
    FACING_PREV;
enum KEYS
{
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
extern Uint8 *key_state;
Uint8 *key_state;
union SDL_Event ev;

/** 
 * UP:
 * If user is pressing up, 
 * set the value of key_states[SDL_SCANCODE_W] to 0 and return true, 
 * otherwise return false 
 */
int UP();

/** 
 * LEFT:
 * If user is pressing left, 
 * set the value of key_states[SDL_SCANCODE_A] to 0 and return true, 
 * otherwise return false 
 */
int LEFT();

/** 
 * RIGHT:
 * If user is pressing right, 
 * set the value of key_states[SDL_SCANCODE_D] to 0 and return true, 
 * otherwise return false 
 */
int RIGHT();

/** 
 * DOWN:
 * If user is pressing down, 
 * set the value of key_states[SDL_SCANCODE_S] to 0 and return true, 
 * otherwise return false 
 */
int DOWN();

/** 
 * CONFIRM:
 * If user is pressing the confirm button, 
 * set the value of key_states[SDL_SCANCODE_J] to 0 and return true, 
 * otherwise return false 
 */
int CONFIRM();

/** 
 * CANCEL:
 * If user is pressing the cancel button, 
 * set the value of key_states[SDL_SCANCODE_L] to 0 and return true, 
 * otherwise return false 
 */
int CANCEL();

/** 
 * EXIT:
 * If user is pressing the exit button, 
 * set the value of key_states[SDL_SCANCODE_O] to 0 and return true, 
 * otherwise return false 
 */
int EXIT();

/** 
 * FULL:
 * If user is pressing the activate fullscreen button, 
 * set the value of key_states[SDL_SCANCODE_F] to 0 and return true, 
 * otherwise return false 
 */
int FULL();

int NOTHING_PRESSED();

#endif