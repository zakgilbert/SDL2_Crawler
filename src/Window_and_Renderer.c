#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include "Window_and_Renderer.h"
#include "Header.h"

/* Create and return an SDL window object */
SDL_Window *make_window(char *name)
{
    struct SDL_Window *window = NULL;
    window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, 0);
    if (!window)
    {
        printf("\nERROR: SDL window failed--\n%s\n", SDL_GetError());
    }
    return window;
}

/* Create and return and SDL renderer */
SDL_Renderer *make_renderer(SDL_Window **window)
{
    Uint32 render_flags;
    SDL_Renderer *renderer = NULL;
    render_flags = SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE;

    renderer = SDL_CreateRenderer(*window, -1, render_flags);

    if (!renderer)
    {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_Quit();
    }
    return renderer;
}

/* Create a texture from an image file and a pointer to be referenced during rendering */
struct SDL_Texture *create_texture(struct SDL_Renderer *renderer, const char *path, struct SDL_Rect *rect)
{
    struct SDL_Texture *texture = NULL;
    struct SDL_Surface *surface = NULL;

    surface = IMG_Load(path);

    if (!surface)
    {
        printf("error creating surface: %s\n", SDL_GetError());
        SDL_Quit();
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        printf("error creating Texture: %s\n", SDL_GetError());
        SDL_Quit();
    }
    SDL_QueryTexture(texture, NULL, NULL, &rect->w, &rect->h);
    return texture;
}

void set_full_screen(int full_screen, SDL_Window *window)
{
    if (full_screen)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    else
        SDL_SetWindowFullscreen(window, 0);
}

void set_rect(SDL_Rect *rect, int x, int y, int w, int h)
{
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}
int get_middle_x(int frame_size, int sprite_size)
{
    return (frame_size / 2) - (sprite_size / 2);
}
int get_middle_y(int frame_size, int sprite_size)
{
    return (frame_size / 2) - (sprite_size / 2);
}
void set_fullscreen(SDL_Window *window)
{
    if (FULLSCREEN_ON)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    else
    {
        SDL_SetWindowFullscreen(window, 0);
    }
}