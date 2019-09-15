#ifndef LINE_H
#define LINE_H

typedef struct _Atlas Atlas;

/**
 * Hastable node which holds values needed to render a letter.
 * The field "letter" is the key.
 */
struct Letter
{
    const char *letter;
    SDL_Rect rect;
    SDL_Texture *texture;
};

/**
 * Return a new struct Letter
 */
struct Letter *NEW_LETTER(const char *letter, int x, int y);

/**
 * Encapsule or render a line of letter nodes from the font atlas
 */
typedef struct _Line
{
    void (*render_letter)(SDL_Renderer *renderer,
                          SDL_Texture *texture, SDL_Rect *rect); /* Render letter texture */
    void (*destroy)(struct _Line *this);                         /* Free allocated memory */
    SDL_Texture *(*get_texture)(struct _Line *this, int i);      /* Set the correct x and y coords to a letter. */
    void (*set_letters)(struct _Line *this);                     /* Add the letters to the line. */

    struct Letter **letters; /* All the letters in the line */
    Atlas *atlas;            /* Font atlas */
    int num_let;             /* Number of letters in line */
    const char *line;        /* The line of letters */
    int x, y;                /* Current x and y coordinates of line */
    int inc;                 /* index of current letter in line */

} Line;

Line *CREATE_LINE(Atlas *atlas, const char *line, int x, int y, int inc);
void render_line(void *obj, SDL_Renderer *renderer);
void destroy_line(void *obj);
void render_char(void *obj, SDL_Renderer *renderer);
#endif /* LINE_H */
