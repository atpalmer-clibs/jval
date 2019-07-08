#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jobj.h"
#include "jcollection.h"


static void jprop_destroy(const struct jprop *self) {
    free((void *)self->name);
    jval_cleanup(&self->jval);
}


static struct jval *jobj_new_prop(struct jobj *self, const char *name) {
    struct jprop *new_prop = jcollection_new_entry((struct jcollection *)self, sizeof *self->props);
    new_prop->name = strdup(name);
    return &new_prop->jval;
}


static struct jval *jarr_new_val(struct jarr *self) {
    struct jval *new_val = jcollection_new_entry((struct jcollection *)self, sizeof *self->vals);
    return new_val;
}


struct jarr *jarr_new(void) {
    struct jarr *new = (struct jarr *)jcollection_new(sizeof *new->vals);
    return new;
}


void jarr_destroy(const struct jarr *self) {
    for(int i = 0; i < self->count; ++i) {
        jval_cleanup(&self->vals[i]);
    }
    free((void *)self->vals);
    free((void *)self);
}


void jarr_to_console(struct jarr *self) {
    for(int i = 0; i < self->count; ++i) {
        jval_to_console(&self->vals[i]);
        printf("\n");
    }
}


void jarr_add_long(struct jarr *self, long value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_INTEGER;
    new_val->value.as_long = value;
}


void jarr_add_double(struct jarr *self, double value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_NUMBER;
    new_val->value.as_double = value;
}


void jarr_add_string(struct jarr *self, const char *value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_STRING;
    new_val->value.as_string = strdup(value);
}


void jarr_add_jarr(struct jarr *self, struct jarr *value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_ARRAY;
    new_val->value.as_jarr = value;
}


void jarr_add_jobj(struct jarr *self, struct jobj *value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_OBJECT;
    new_val->value.as_jobj = value;
}


struct jobj *jobj_new(void) {
    struct jobj *new = (struct jobj *)jcollection_new(sizeof *new->props);
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


void jobj_add_jarr(struct jobj *self, const char *name, struct jarr *value) {
    struct jval *new_val = jobj_new_prop(self, name);
    new_val->type = JTYPE_ARRAY;
    new_val->value.as_jarr = value;
}


void jobj_add_jobj(struct jobj *self, const char *name, struct jobj *value) {
    struct jval *new_val = jobj_new_prop(self, name);
    new_val->type = JTYPE_OBJECT;
    new_val->value.as_jobj = value;
}
