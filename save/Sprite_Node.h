#ifndef SPRITE_NODE_H
#define SPRITE_NODE_H

typedef struct _Logic_Node Logic_Node;

typedef Logic_Node *render_function_t(void *obj, struct SDL_Renderer *renderer);

typedef struct _Sprite_Node
{
    void (*destroy)(struct _Sprite_Node *this);
    render_function_t(*render);

    SDL_Texture *text;
    SDL_Rect rect;
    int tag;

} Sprite_Node;
Sprite_Node *CREATE_SPRITE_NODE(int x, int y);

#endif /* SPRITE_NODE_H */
