#include "jtypes/jtypes.h"


static void jobj_entry_destroy(const struct jobj_entry *self)
{
    free((void *)self->name);
    jval_cleanup(&self->value);
}

static struct jval *jobj_new_entry(struct jobj *self, const char *name)
{
    struct jobj_entry *new = jcollection_new_entry((struct jcollection *)self, sizeof *self->entries);
    new->name = strdup(name);
    return &new->value;
}

struct jobj *jobj_new(void)
{
    struct jobj *new = (struct jobj *)jcollection_new(sizeof *new->entries);
    return new;
}

void jobj_destroy(const struct jobj *self)
{
    for (size_t i = 0; i < self->count; ++i) {
        jobj_entry_destroy(&self->entries[i]);
    }
    free((void *)self->entries);
    free((void *)self);
}

void jobj_add_long(struct jobj *self, const char *name, long value)
{
    struct jval *new_val = jobj_new_entry(self, name);
    new_val->type = JTYPE_INTEGER;
    new_val->value.as_long = value;
}

void jobj_add_double(struct jobj *self, const char *name, double value)
{
    struct jval *new_val = jobj_new_entry(self, name);
    new_val->type = JTYPE_NUMBER;
    new_val->value.as_double = value;
}

void jobj_add_bool(struct jobj *self, const char *name, int value)
{
    struct jval *new_val = jobj_new_entry(self, name);
    new_val->type = JTYPE_BOOL;
    new_val->value.as_bool = value;
}

void jobj_add_string(struct jobj *self, const char *name, const char *value)
{
    if (!value) {
        jobj_add_null(self, name);
        return;
    }
    struct jval *new_val = jobj_new_entry(self, name);
    new_val->type = JTYPE_STRING;
    new_val->value.as_string = strdup(value);
}

void jobj_add_jarr(struct jobj *self, const char *name, struct jarr *value)
{
    if (!value) {
        jobj_add_null(self, name);
        return;
    }
    struct jval *new_val = jobj_new_entry(self, name);
    new_val->type = JTYPE_ARRAY;
    new_val->value.as_jarr = value;
}

void jobj_add_jobj(struct jobj *self, const char *name, struct jobj *value)
{
    if (!value) {
        jobj_add_null(self, name);
        return;
    }
    struct jval *new_val = jobj_new_entry(self, name);
    new_val->type = JTYPE_OBJECT;
    new_val->value.as_jobj = value;
}

void jobj_add_null(struct jobj *self, const char *name)
{
    struct jval *new_val = jobj_new_entry(self, name);
    new_val->type = JTYPE_NULL;
    new_val->value.as_ptr= NULL;
}
