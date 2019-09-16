
#ifndef GRAPHICS_H
#define GRAPHICS_H

/* Initiate SDL */
void SDL_init();

/* Create and return an SDL window object */
SDL_Window* make_window(char*);

/* Create and return and SDL renderer */
SDL_Renderer* make_renderer(SDL_Window** window);

/* Create a texture from an image file and a pointer to be referenced during rendering */
SDL_Texture* create_texture(SDL_Renderer* renderer, const char* path, SDL_Rect* rect);

/* set hint and logical size of full screen */
void set_render_options(SDL_Renderer* renderer);

/* Set a SDL Rectangles fields */
void set_rect(SDL_Rect* rect, int x, int y, int w, int h);

/* Return the middle x coordinate for a texture to be centered to the frame */
int get_middle_x(int frame_size, int sprite_size);

/* Return the middle y coordinate for a texture to be centered to the frame */
int get_middle_y(int frame_size, int sprite_size);

/* If user KEY = F turn fullscreen on or off */
void set_fullscreen(SDL_Window* window);

#endif //GRAPHICS_H
