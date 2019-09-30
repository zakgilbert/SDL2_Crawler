#ifndef RECT_NODE_H
#define RECT_NODE_H

typedef struct _Rect_Node {
    void (*destroy)(struct _Rect_Node* this);                    /* Free Allocated Memory */
    void (*print)(struct _Rect_Node* this, const char* message); /* Print address of Rect_Node type with message */

    SDL_Rect* rect;
    struct _Rect_Node* next;
} Rect_Node;
Rect_Node* CREATE_RECT_NODE(SDL_Rect* rect);

#endif /* RECT_NODE_H */
