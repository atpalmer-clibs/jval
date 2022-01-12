#include "jtypes/jtypes.h"


static void jval_object_entry_destroy(struct jval_object_entry *entry)
{
    free((void *)entry->name);
    jval_destroy(entry->value);
}

typedef void (*entry_destroy_func)(void *);

static void jval_container_destroy(struct jval_container *self, entry_destroy_func entry_destroy)
{
    for (size_t i = 0; i < self->count; ++i)
        entry_destroy(self->entries[i]);
    free(self);
}

void jval_object_container_destroy(struct jval_container *self)
{
    jval_container_destroy(self, (entry_destroy_func)jval_object_entry_destroy);
}

void jval_array_container_destroy(struct jval_container *self)
{
    jval_container_destroy(self, (entry_destroy_func)jval_destroy);
}

struct jval_container *jval_container_new(void)
{
    static const size_t INITIAL_CAPACITY = 1;
    struct jval_container *new = malloc(sizeof *new + (INITIAL_CAPACITY * sizeof new->entries[0]));
    new->count = 0;
    new->capacity = INITIAL_CAPACITY;
    return new;
}

void jval_container_append(struct jval_container **self, void *entry)
{
    while ((*self)->count >= (*self)->capacity) {
        size_t new_cap = (*self)->capacity * 2;
        *self = realloc(*self, sizeof **self + (new_cap * sizeof((*self)->entries[0])));
        (*self)->capacity = new_cap;
    }

    (*self)->entries[(*self)->count] = entry;
    ++(*self)->count;
}
