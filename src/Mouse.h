#ifndef MOUSE_H
#define MOUSE_H

typedef struct SDL_Renderer SDL_Renderer;

/**
 * Mouse object  
 * ^. .^
 */
typedef struct _Mouse
{
    void (*destroy)(struct _Mouse *this);            /* Free memory allocated for Mouse object */
    int (*get_x)(struct _Mouse *this);               /* Get mouse X coordinate after click, depreciated */
    int (*get_y)(struct _Mouse *this);               /* Get mouse X coordinate after click  depreciated */
    int (*on_click)(struct _Mouse *this, int state); /* If a valid click has occurred set the mouse coordinates and return true, else return false */
    void (*get_state)(struct _Mouse *this);          /* Call the SDL_GetMouseState function */

    int x, y;         /* Local x and y coordinate variables of mouse location */
    int clk_x, clk_y; /* x and y coordinates of last click */
    int lock;         /* The mouse lock */
    int bool;         /* The mouse bool */
    int rect_size;    /* Size of rect that is to be referenced in get_x() and get_y() */
} Mouse;
Mouse *CREATE_MOUSE(int rect_size);
#endif /* MOUSE_H */
