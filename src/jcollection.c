#include "jtypes/jtypes.h"


struct jcollection *jcollection_new(void)
{
    static const size_t INITIAL_CAPACITY = 1;
    struct jcollection *new = malloc(sizeof *new + (INITIAL_CAPACITY * sizeof new->entries[0]));
    new->count = 0;
    new->capacity = INITIAL_CAPACITY;
    return new;
}

void jcollection_add_entry(struct jcollection **self, void *entry)
{
    while ((*self)->count >= (*self)->capacity) {
        size_t new_cap = (*self)->capacity * 2;
        *self = realloc(*self, sizeof **self + (new_cap * sizeof((*self)->entries[0])));
        (*self)->capacity = new_cap;
    }

    (*self)->entries[(*self)->count] = entry;
    ++(*self)->count;
}

void jval_cleanup(const struct jval *self)
{
    if (self->type == JTYPE_OBJECT)
        jobj_destroy(self->value.as_ptr);
    if (self->type == JTYPE_ARRAY)
        jarr_destroy(self->value.as_ptr);
    if (self->type == JTYPE_STRING)
        free(self->value.as_ptr);
}
