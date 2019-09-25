#include <SDL2/SDL.h>
#include "Header.h"
#include "Render_Node.h"
#include "Render_Table.h"

/**
 * static Wrapper function for void (*_Render_Node::print)(struct _Render_Node *this, int i)
 * Prints all fields of node along with its address in memory and the index of which it has been stored in the hashtable
 */
static void print_node(Render_Node* node, int i)
{
    node->print(node, i);
}

static int check_size(int size, int count)
{
    if (count >= size)
        return 1;
    return 0;
}

/**
 * Creates hash code from a char *, prime number, and the size of the hash table.
 */
static int hash(char* str, int prime, int size)
{
    long hash = 0;
    int i;
    const int len = strlen(str);
    for (i = 0; i < len; i++) {
        hash += (long)pow(prime, len - (i + 1)) * str[i];
        hash = hash % size;
    }
    return (int)hash;
}

/**
 * Creates hash code by passing two different prime numbers into <int hash(char * , int, int)
 */
static int hash_code(char* str, const int num, const int attempt)
{
    int hash_a = hash(str, PRIME_1, num);
    int hash_b = hash(str, PRIME_2, num);
    return (hash_a + (attempt * (hash_b + 1))) % num;
}

/**
 * Deallocates all memory that of which was allocated at the hashtables creation.
 */
static void _destroy(Render_Table* this)
{
    Render_Node* temp  = NULL;
    Render_Node* dummy = NULL;
    if (NULL != this) {
        if (PRINT)
            printf("\n  Deallocating Render_Table Table            %p\n\n", this);
        for (size_t i = 0; i < this->size; i++) {
            temp = this->table[i];
            if (NULL != temp) {
                this->table[i] = dummy;
                temp->destroy(temp);
            }
        }
        free(this->table);
        free(this);
    }
}

/**
 * Performs a hash search for the given key
 */
static Render_Node* _search(Render_Table* this, char* key)
{
    int index         = hash_code(key, this->size, 0);
    Render_Node* item = this->table[index];
    int i             = 1;
    while (NULL != item) {
        if (strcmp(item->key, key) == 0)
            return item;
        index = hash_code(key, this->size, i);
        i++;
    }
    return NULL;
}

/**
 * Prints Render_Tabletable
 */
static void _print_table(Render_Table* this)
{
    printf("\n      Printing Table\n\n");
    for (int i = 0; i < this->size; i++) {
        if (NULL != this->table[i]) {
            print_node(this->table[i], i);
            printf("%*s\n", 10, "Printing");
        }
    }
}

/**
 * Doubles the size of the hashtable
 */
static void _grow(Render_Table* this)
{
    Render_Node** temp;
    Render_Node *dummy, *temp_n;
    int old_size;

    temp        = this->table;
    dummy       = NULL;
    temp_n      = NULL;
    old_size    = this->size;
    this->size  = old_size * 2;
    this->table = realloc(this->table, (sizeof(Render_Node*)) * (this->size));
    this->count = 0;
    printf("\n       Resizing Render_Table Table               %p\n\n", this->table);
    for (int i = 0; i < old_size; i++) {
        temp_n = temp[i];
        if (NULL != temp_n) {
            this->insert(this, CREATE_RENDER_NODE(temp_n->key, temp_n->obj, temp_n->funct));
            this->table[i] = dummy;
            temp_n->destroy(temp_n);
        }
    }
    free(temp);
}

/**
 * Inserts a new node into hashtable.
 */
static void _insert(Render_Table* this, Render_Node* item)
{
    int index             = hash_code(item->key, this->size, 0);
    Render_Node* cur_item = this->table[index];
    int i                 = 1;
    if (check_size(this->size, this->count) == 1)
        this->grow(this);
    while (NULL != cur_item) {
        index    = hash_code(item->key, this->size, i);
        cur_item = this->table[index];
        i++;
    }
    this->table[index]        = item;
    this->table[index]->index = index;
    if (PRINT) {
        print_node(this->table[index], index);
        printf("%*s\n", 10, "Added");
    }
    this->count++;
}

/**
 * Deletes node of key
 */
static void _delete(Render_Table* this, char* key)
{
    Render_Node* item  = this->search(this, key);
    Render_Node* dummy = NULL;
    if (item) {
        this->table[item->index] = dummy;
        item->destroy(item);
        this->count--;
    } else
        printf("The node with a key value %s was not found\n", key);
}

Render_Table* CREATE_RENDER_TABLE(int size)
{
    Render_Table* this = malloc(sizeof(*this));
    this->size         = size;
    this->table        = malloc(sizeof(Render_Node*) * this->size);
    for (int i = 0; i < this->size; i++) {
        this->table[i] = NULL;
    }

    this->destroy     = _destroy;
    this->search      = _search;
    this->print_table = _print_table;
    this->grow        = _grow;
    this->insert      = _insert;
    this->delete      = _delete;
    this->count       = 0;
    if (PRINT)
        printf("\n  Allocating Render_Table Table              %p\n\n", this);
    return this;
}
