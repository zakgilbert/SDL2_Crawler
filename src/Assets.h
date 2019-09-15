#ifndef ASSETS_H
#define ASSETS_H

typedef struct _Floor Floor;
typedef struct _Hash_l Hash_l;
typedef struct _Hash_r Hash_r;
typedef struct _Logic_Node Logic_Node;
typedef struct _Render_Node Render_Node;
struct Table_Container
{
    Hash_l *t_l;
    Hash_r *t_r;
};
struct Table_Container add_asset(Hash_l *t_l, Hash_r *t_r, SDL_Renderer *renderer);

Hash_r *add_render(Hash_r *table, SDL_Renderer *renderer);

char **create_state(int *states, int num, char **state);
int *get_dark_forest_render();
int *get_dark_forest_logic();

void draw(Hash_r *table, char **state, SDL_Renderer *renderer, int num);
void logic(Hash_l *table, char **state, int num);
#endif /* ASSETS_H */
