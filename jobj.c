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


static struct jval *jobj_new_prop(struct jobj *self, const char *name) {
    if(self->count == self->capacity) {
        size_t new_cap = self->capacity * 2;
        self->props = realloc(self->props, new_cap * sizeof *self->props);
        self->capacity = new_cap;
    }

    struct jprop *new_prop = &self->props[self->count];
    new_prop->name = strdup(name);
    ++self->count;
    return &new_prop->jval;
}


static struct jval *jarr_new_val(struct jarr *self) {
    if(self->count == self->capacity) {
        size_t new_cap = self->capacity * 2;
        self->vals = realloc(self->vals, new_cap * sizeof *self->vals);
        self->capacity = new_cap;
    }

    struct jval *new_val = &self->vals[self->count];
    ++self->count;
    return new_val;
}


static void jval_to_console(struct jval *self) {
    if(self->type == JTYPE_INTEGER)
        printf("%ld", self->value.as_long);
    if(self->type == JTYPE_NUMBER)
        printf("%f", self->value.as_double);
    if(self->type == JTYPE_STRING)
        printf("%s", self->value.as_string);
}


struct jarr *jarr_new(void) {
    static const size_t INITIAL_CAPACITY = 1;
    struct jarr *new = malloc(sizeof *new);
    new->count = 0;
    new->capacity = INITIAL_CAPACITY;
    new->vals = malloc(INITIAL_CAPACITY * sizeof *new->vals);
    return new;
}


void jarr_destroy(const struct jarr *self) {
    for(int i = 0; i < self->count; ++i) {
        jval_cleanup(&self->vals[i]);
    }
    free((void *)self->vals);
    free((void *)self);
}


void jarr_add_long(struct jarr *self, long value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_INTEGER;
    new_val->value.as_long = value;
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
        printf("%s: ", prop->name);
        jval_to_console(&prop->jval);
        printf("\n");
    }
}


void jobj_add_long(struct jobj *self, const char *name, long value) {
    struct jval *new_val = jobj_new_prop(self, name);
    new_val->type = JTYPE_INTEGER;
    new_val->value.as_long = value;
}


void jobj_add_double(struct jobj *self, const char *name, double value) {
    struct jval *new_val = jobj_new_prop(self, name);
    new_val->type = JTYPE_NUMBER;
    new_val->value.as_double = value;
}


void jobj_add_string(struct jobj *self, const char *name, const char *value) {
    struct jval *new_val = jobj_new_prop(self, name);
    new_val->type = JTYPE_STRING;
    new_val->value.as_string = strdup(value);
}
