#include "jtypes/jtypes.h"


struct jval *jval_ensure_type(struct jval *self, enum jtype type)
{
    if (self->type != type)
        abort();
    return self;
}

static struct jval *jval_or_jnull(struct jval *self)
{
    if (self)
        return self;
    return jval_new_null();
}

void jval_append(struct jval *self, struct jval *value)
{
    jval_ensure_type(self, JTYPE_ARRAY);
    jval_container_append(&self->value.as_container, jval_or_jnull(value));
}

void jval_set(struct jval *self, const char *name, struct jval *value)
{
    jval_ensure_type(self, JTYPE_OBJECT);

    struct jval_object_entry *new = malloc(sizeof *new);
    new->name = strdup(name);
    new->value = jval_or_jnull(value);

    jval_container_append(&self->value.as_container, new);
}

struct jval *jval_from_long(long value)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JTYPE_INTEGER;
    new->value.as_long = value;
    return new;
}

struct jval *jval_from_double(double value)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JTYPE_NUMBER;
    new->value.as_double = value;
    return new;
}

struct jval *jval_from_bool(int value)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JTYPE_BOOL;
    new->value.as_bool = value;
    return new;
}

struct jval *jval_from_string(const char *value)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JTYPE_STRING;
    new->value.as_string = strdup(value);
    return new;
}

struct jval *jval_new_array(void)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JTYPE_ARRAY;
    new->value.as_container = jval_container_new();
    return new;
}

struct jval *jval_new_object(void)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JTYPE_OBJECT;
    new->value.as_container = jval_container_new();
    return new;
}

struct jval *jval_new_null(void)
{
    struct jval *new = calloc(sizeof *new, 1);
    new->type = JTYPE_NULL;
    return new;
}

void jval_destroy(struct jval *self)
{
    if (self->type == JTYPE_OBJECT)
        jval_object_container_destroy(self->value.as_container);
    if (self->type == JTYPE_ARRAY)
        jval_array_container_destroy(self->value.as_container);
    if (self->type == JTYPE_STRING)
        free((void *)self->value.as_string);
    free(self);
}
