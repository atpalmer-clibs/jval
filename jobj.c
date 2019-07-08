#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jobj.h"


static void jval_cleanup(const struct jval *self) {
    if(self->type == JTYPE_OBJECT)
        jobj_destroy(self->value.as_ptr);
    if(self->type == JTYPE_STRING)
        free(self->value.as_ptr);
}


static void jprop_destroy(const struct jprop *self) {
    free((void *)self->name);
    jval_cleanup(&self->jval);
}


static struct jprop *jobj_new_prop(struct jobj *self) {
    if(self->count == self->capacity) {
        size_t new_cap = self->capacity * 2;
        self->props = realloc(self->props, new_cap * sizeof *self->props);
        self->capacity = new_cap;
    }

    struct jprop *result = &self->props[self->count];
    ++self->count;
    return result;
}


struct jobj *jobj_new(void) {
    static const size_t INITIAL_CAPACITY = 1;
    struct jobj *new = malloc(sizeof *new);
    new->count = 0;
    new->capacity = INITIAL_CAPACITY;
    new->props = malloc(INITIAL_CAPACITY * sizeof *new->props);
    return new;
}


void jobj_destroy(const struct jobj *self) {
    for(int i = 0; i < self->count; ++i) {
        jprop_destroy(&self->props[i]);
    }
    free((void *)self->props);
    free((void *)self);
}


void jobj_to_console(struct jobj *self) {
    for(int i = 0; i < self->count; ++i) {
        struct jprop *prop = &self->props[i];
        if(prop->jval.type == JTYPE_NUMBER)
            printf("%s: %f\n", prop->name, prop->jval.value.as_double);
        if(prop->jval.type == JTYPE_STRING)
            printf("%s: %s\n", prop->name, prop->jval.value.as_string);
    }
}


void jobj_add_double(struct jobj *self, const char *name, double value) {
    struct jprop *new_prop = jobj_new_prop(self);
    new_prop->name = strdup(name);
    new_prop->jval.type = JTYPE_NUMBER;
    new_prop->jval.value.as_double = value;

}


void jobj_add_string(struct jobj *self, const char *name, const char *value) {
    struct jprop *new_prop = jobj_new_prop(self);
    new_prop->name = strdup(name);
    new_prop->jval.type = JTYPE_STRING;
    new_prop->jval.value.as_string = strdup(value);
}
