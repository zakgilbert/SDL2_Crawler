#ifndef DIRECTION_H
#define DIRECTION_H

/**
 * Encapsule the functions necessary for controling how the screen moves
 */
typedef struct _Direction {
    void (*destroy)(struct _Direction* this);           /* Deallocate strucrt memory */
    char* (*render)(void* obj, SDL_Renderer* renderer); /* Render struct graphics(empty function) */
    char* (*logic)(void* obj);                          /* Perform directional logic */

    void (*hit_functions[8])(int x, int y);   /* Array of directional functions */
    void (*move_functions[17])(int x, int y); /* Array of directional functions */
    char* key;                                /* Object Key for logic and render Q's */
} Direction;
Direction* CREATE_DIRECTION(char* key);

void move_down(int x, int y);
void move_down_down_left(int x, int y);
void move_down_left(int x, int y);
void move_down_left_left(int x, int y);
void move_left(int x, int y);
void move_up_left_left(int x, int y);
void move_up_left(int x, int y);
void move_up_up_left(int x, int y);
void move_up(int x, int y);
void move_up_up_right(int x, int y);
void move_up_right(int x, int y);
void move_up_right_right(int x, int y);
void move_right(int x, int y);
void move_down_right_right(int x, int y);
void move_down_right(int x, int y);
void move_down_down_right(int x, int y);

void hit_down(int x, int y);
void hit_down_left(int x, int y);
void hit_left(int x, int y);
void hit_up_left(int x, int y);
void hit_up(int x, int y);
void hit_up_right(int x, int y);
void hit_right(int x, int y);
void hit_down_right(int x, int y);

int WALK_F(int close);
int ATTACK_1_F(int close);
int ATTACK_2_F(int close);
int RUN_F(int close);
int STANCE_F(int close);
int CONFIRM(int close);
int CANCEL(int close);
int EXIT(int close);
int FULL(int close);
int NOTHING_PRESSED(int close);
#endif /* DIRECTION_H */
