#ifndef COLLISION_H
#define COLLISION_H
typedef struct _Rect_Node Rect_Node;
typedef struct _Collision {
    void (*destroy)(struct _Collision* this);                    /* Free Allocated Memory */
    void (*print)(struct _Collision* this, const char* message); /* Print address of Collision type with message */
    void (*add)(struct _Collision* this, Rect_Node* node);
    char* (*render)(void* obj, SDL_Renderer* renderer);
    char* (*logic)(void* obj);

    Rect_Node* head;
    SDL_Rect* ref;
    SDL_Rect* inter;
    char* key;

} Collision;
Collision* CREATE_COLLISION(char* key, SDL_Rect* ref);

#endif /* COLLISION_H */
