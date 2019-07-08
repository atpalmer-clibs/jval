#include <stdio.h>
#include <stdlib.h>
#include "jcollection.h"
#include "jobj.h"


struct jcollection *jcollection_new(size_t entry_size) {
    static const size_t INITIAL_CAPACITY = 1;
    struct jcollection *new = malloc(sizeof *new);
    new->count = 0;
    new->capacity = INITIAL_CAPACITY;
    new->entries = malloc(INITIAL_CAPACITY * entry_size);
    return new;
}


void *jcollection_new_entry(struct jcollection *self, size_t entry_size) {
    if(self->count == self->capacity) {
        size_t new_cap = self->capacity * 2;
        self->entries = realloc(self->entries, new_cap * entry_size);
        self->capacity = new_cap;
    }

    void *new_entry = &((char *)self->entries)[self->count * entry_size];
    ++self->count;
    return new_entry;
}


void jval_cleanup(const struct jval *self) {
    if(self->type == JTYPE_OBJECT)
        jobj_destroy(self->value.as_ptr);
    if(self->type == JTYPE_ARRAY)
        jarr_destroy(self->value.as_ptr);
    if(self->type == JTYPE_STRING)
        free(self->value.as_ptr);
}


void jval_to_console(struct jval *self) {
    if(self->type == JTYPE_INTEGER)
        printf("%ld", self->value.as_long);
    if(self->type == JTYPE_NUMBER)
        printf("%f", self->value.as_double);
    if(self->type == JTYPE_STRING)
        printf("%s", self->value.as_string);
    if(self->type == JTYPE_ARRAY)
        jarr_to_console(self->value.as_jarr);
    if(self->type == JTYPE_OBJECT)
        jobj_to_console(self->value.as_jobj);
}
