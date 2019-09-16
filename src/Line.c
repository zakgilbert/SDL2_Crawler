
/************************
	 *  Line.c
	*/

#include <SDL2/SDL.h>

#include "Alpha_Node.h"
#include "Atlas.h"
#include "Header.h"
#include "Line.h"

/**
 * Return a new struct Letter
 */
struct Letter* NEW_LETTER(const char* letter, int x, int y)
{
    struct Letter* new_letter = malloc(sizeof(struct Letter));
    new_letter->letter = strdup(letter);
    new_letter->rect.x = x;
    new_letter->rect.y = y;
    return new_letter;
}

/* Free memory allocated for Line object */
static void _destroy(Line* this)
{
    int i;

    if (NULL != this) {
        for (i = 0; i < this->num_let - 1; i++) {
            if (NULL != this->letters[i])
                free(this->letters[i]);
        }

        free(this->letters);
        this->letters = NULL;
        free(this);
        this = NULL;
    }
}

/* Render letter is called in render_line which is a function to be sent to the render_q*/
static void _render_letter(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* rect)
{
    SDL_RenderCopy(renderer, texture, NULL, rect);
}

/**
 * Sets the correct x and y coords to a letter.
 */
struct SDL_Texture* _get_texture(Line* this, int i)
{
    Alpha_Node* item = this->atlas->search(this->atlas, this->letters[i]->letter);
    int inc = this->inc;
    this->letters[i]->rect.x = this->x;
    this->letters[i]->rect.w = item->rect.w;
    this->letters[i]->rect.h = item->rect.h;
    this->x += item->rect.w + 1;

    if ((strcmp(item->key, "g") == 0) || (strcmp(item->key, "q") == 0) || (strcmp(item->key, "j") == 0) || (strcmp(item->key, "y")) == 0)
        this->letters[i]->rect.y = this->y + 3 * inc;
    else if ((strcmp(item->key, "i") == 0))
        this->letters[i]->rect.y = this->y + 1 * inc;
    else if (item->rect.h < (8 * inc) && (strcmp(item->key, "h") != 0))
        this->letters[i]->rect.y = this->y + 2 * inc;
    else
        this->letters[i]->rect.y = this->y;
    return item->texture;
}

/**
 * Adds the letters to the line.
 */
static void _set_letters(Line* this)
{
    int i = 0;
    char buff[1];
    for (; i < this->num_let; i++) {
        buff[0] = this->line[i];
        this->letters[i] = NEW_LETTER(buff, this->x, this->y);
        this->letters[i]->texture = this->get_texture(this, i);
    }
}
Line* CREATE_LINE(Atlas* atlas, const char* line, int x, int y, int inc)
{
    Line* this = malloc(sizeof(*this));

    this->destroy = _destroy;
    this->render_letter = _render_letter;
    this->set_letters = _set_letters;
    this->get_texture = _get_texture;

    this->atlas = atlas;
    this->line = line;
    this->x = x;
    this->y = y;
    this->inc = inc;
    this->num_let = strlen(this->line);
    this->letters = calloc(this->num_let, sizeof(struct Letter*));
    this->set_letters(this);

    return this;
}
void render_line(void* obj, struct SDL_Renderer* renderer)
{
    int i;
    Line* this = (Line*)obj;
    for (i = 0; i < this->num_let; i++) {
        this->render_letter(renderer, this->letters[i]->texture, &this->letters[i]->rect);
    }
}
void destroy_line(void* obj)
{
    Line* this = (Line*)obj;
    this->destroy(this);
}

void render_char(void* obj, struct SDL_Renderer* renderer)
{
    struct Letter* l = (struct Letter*)obj;
    SDL_RenderCopy(renderer, l->texture, NULL, &l->rect);
}