#ifndef ASSETS_H
#define ASSETS_H

typedef struct _Floor Floor;
typedef struct _Logic_Table Logic_Table;
typedef struct _Render_Table Render_Table;
typedef struct _Logic_Node Logic_Node;
typedef struct _Render_Node Render_Node;
struct Table_Container
{
    Logic_Table *t_l;
    Render_Table *t_r;
};
struct Table_Container add_assets(Logic_Table *t_l, Render_Table *t_r, SDL_Renderer *renderer);

Render_Table *add_render(Render_Table *table, SDL_Renderer *renderer);

char **create_state(int *states, int num, char **state);
int *get_dark_forest_render();
int *get_dark_forest_logic();

void draw(Render_Table *table, char **state, SDL_Renderer *renderer, int num);
void logic(Logic_Table *table, char **state, int num);
#endif /* ASSETS_H */
