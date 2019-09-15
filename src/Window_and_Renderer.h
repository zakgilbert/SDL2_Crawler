
#ifndef WINDOW_AND_RENDERER_H
#define WINDOW_AND_RENDERER_H

/* Create and return an SDL window object */
SDL_Window *make_window(char *);

/* Create and return and SDL renderer */
SDL_Renderer *make_renderer(SDL_Window **window);

/* Create a texture from an image file and a pointer to be referenced during rendering */
SDL_Texture *create_texture(SDL_Renderer *renderer, const char *path, SDL_Rect *rect);

void set_full_screen(int full_screen, SDL_Window *window);
void set_rect(SDL_Rect *rect, int x, int y, int w, int h);
int get_middle_x(int frame_size, int sprite_size);
int get_middle_y(int frame_size, int sprite_size);
void set_fullscreen(SDL_Window *window);
#endif //WINDOW_AND_RENDERER_H
