#include "jtypes/jtypes.h"


static void jobj_entry_destroy(const struct jobj_entry *self)
{
    free((void *)self->name);
    jval_destroy(self->value);
}

void jobj_destroy(const struct jobj *self)
{
    for (size_t i = 0; i < self->count; ++i)
        jobj_entry_destroy(self->entries[i]);
    free((void *)self);
}

static void jobj_add_jval(struct jobj **self, const char *name, struct jval *value)
{
    struct jobj_entry *new = malloc(sizeof *new);
    new->name = strdup(name);
    new->value = value;
    jcollection_add_entry((struct jcollection **)self, new);
}

void jobj_add_long(struct jobj **self, const char *name, long value)
{
    struct jval *new = jval_from_long(value);
    jobj_add_jval(self, name, new);
}

void jobj_add_double(struct jobj **self, const char *name, double value)
{
    struct jval *new = jval_from_double(value);
    jobj_add_jval(self, name, new);
}

void jobj_add_bool(struct jobj **self, const char *name, int value)
{
    struct jval *new = jval_from_bool(value);
    jobj_add_jval(self, name, new);
}

void jobj_add_string(struct jobj **self, const char *name, const char *value)
{
    if (!value) {
        jobj_add_null(self, name);
        return;
    }
    struct jval *new = jval_from_string(value);
    jobj_add_jval(self, name, new);
}

void jobj_add_jarr(struct jobj **self, const char *name, struct jarr *value)
{
    if (!value) {
        jobj_add_null(self, name);
        return;
    }
    struct jval *new = jval_from_jarr(value);
    jobj_add_jval(self, name, new);
}

void jobj_add_jobj(struct jobj **self, const char *name, struct jobj *value)
{
    if (!value) {
        jobj_add_null(self, name);
        return;
    }
    struct jval *new = jval_from_jobj(value);
    jobj_add_jval(self, name, new);
}

void jobj_add_null(struct jobj **self, const char *name)
{
    struct jval *new = jval_new_null();
    jobj_add_jval(self, name, new);
}
