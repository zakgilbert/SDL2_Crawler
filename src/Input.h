#ifndef JRPG_PLAYER_INPUT_H
#define JRPG_PLAYER_INPUT_H

/**
 * Thread handler for player inputs.
 */
int input_handler(void* data);

/** 
 * UP:
 * If user is pressing up, 
 * set the value of KEY_STATE[SDL_SCANCODE_W] to 0 and return true, 
 * otherwise return false 
 */
int UP();

/** 
 * LEFT:
 * If user is pressing left, 
 * set the value of KEY_STATE[SDL_SCANCODE_A] to 0 and return true, 
 * otherwise return false 
 */
int LEFT();

/** 
 * RIGHT:
 * If user is pressing right, 
 * set the value of KEY_STATE[SDL_SCANCODE_D] to 0 and return true, 
 * otherwise return false 
 */
int RIGHT();

/** 
 * DOWN:
 * If user is pressing down, 
 * set the value of KEY_STATE[SDL_SCANCODE_S] to 0 and return true, 
 * otherwise return false 
 */
int DOWN();

/** 
 * CONFIRM:
 * If user is pressing the confirm button, 
 * set the value of KEY_STATE[SDL_SCANCODE_J] to 0 and return true, 
 * otherwise return false 
 */
int CONFIRM();

/** 
 * CANCEL:
 * If user is pressing the cancel button, 
 * set the value of KEY_STATE[SDL_SCANCODE_L] to 0 and return true, 
 * otherwise return false 
 */
int CANCEL();

/** 
 * EXIT:
 * If user is pressing the exit button, 
 * set the value of KEY_STATE[SDL_SCANCODE_O] to 0 and return true, 
 * otherwise return false 
 */
int EXIT();

/** 
 * FULL:
 * If user is pressing the activate fullscreen button, 
 * set the value of KEY_STATE[SDL_SCANCODE_F] to 0 and return true, 
 * otherwise return false 
 */
int FULL();

int NOTHING_PRESSED();

/**
 * The direction of which the map is moved depends on the angle of the two points...
 *  - p1( (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2) ) 
 *      - this is the middle of the screen
 *  - p2(MOUSE_X, MOUSE_Y)
 * Since there are 16 rows one for every direction in the sprite sheets, 
 * their are 16 variations(quadrants) of angles that differ in how X and Y are changed.
 */

#endif
