#ifndef DIRECTION_H
#define DIRECTION_H

typedef struct _Direction {
    void (*destroy)(struct _Direction* this);
    char* (*render)(void* obj, SDL_Renderer* renderer);
    char* (*logic)(void* obj);

    char* key;
} Direction;
Direction* CREATE_DIRECTION(char* key);

#endif /* DIRECTION_H */
