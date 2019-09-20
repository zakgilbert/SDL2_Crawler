#ifndef SPRITE_NODE_H
#define SPRITE_NODE_H

typedef struct _Sprite Sprite;

typedef struct _Sprite_Node {
    void (*destroy)(struct _Sprite_Node* this);                    /* Free Allocated Memory */
    void (*print)(struct _Sprite_Node* this, const char* message); /* Print address of Sprite_Node type with message */
    
    Sprite* sprite;
    struct _Sprite_Node* next;
} Sprite_Node;
Sprite_Node* CREATE_SPRITE_NODE(Sprite * sprite);

#endif /* SPRITE_NODE_H */
