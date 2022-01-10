#include "jtypes/jtypes.h"


static void jprop_destroy(const struct jprop *self) {
    free((void *)self->name);
    jval_cleanup(&self->jval);
}


static struct jval *jobj_new_prop(struct jobj *self, const char *name) {
    struct jprop *new_prop = jcollection_new_entry((struct jcollection *)self, sizeof *self->props);
    new_prop->name = strdup(name);
    return &new_prop->jval;
}


struct jobj *jobj_new(void) {
    struct jobj *new = (struct jobj *)jcollection_new(sizeof *new->props);
    return new;
}


void jobj_destroy(const struct jobj *self) {
    for(size_t i = 0; i < self->count; ++i) {
        jprop_destroy(&self->props[i]);
    }
    free((void *)self->props);
    free((void *)self);
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
