#ifndef ASSETS_H
#define ASSETS_H

typedef struct _Floor Floor;
typedef struct _Logic_Table Logic_Table;
typedef struct _Render_Table Render_Table;
typedef struct _Logic_Node Logic_Node;
typedef struct _Render_Node Render_Node;

/* A Lazy Containter for logic and render hash tables to be returned at once */
typedef struct _Table_Container {
    Logic_Table* t_l;
    Render_Table* t_r;
} Table_Container;

Table_Container add_assets(Logic_Table* t_l, Render_Table* t_r,
    SDL_Renderer* renderer);                                                     /* Create and add game assets */
char** create_state(int* states, int num, char** state);                         /* Create a list of game states*/
int* get_dark_forest_states();                                                   /* Return the dark forest proper states*/
char** draw(Render_Table* table, char** state, SDL_Renderer* renderer, int num); /* Render to Canvas */
char** logic(Logic_Table* table, char** state, int num);                         /* Execute Game Logic */
#endif                                                                           /* ASSETS_H */
