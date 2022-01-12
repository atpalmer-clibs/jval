#include "jtypes/jtypes.h"


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

struct jval *jval_from_jarr(struct jarr *value)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JTYPE_ARRAY;
    new->value.as_jarr = value;
    return new;
}

struct jval *jval_from_jobj(struct jobj *value)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JTYPE_OBJECT;
    new->value.as_jobj = value;
    return new;
}

struct jval *jval_new_null(void)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JTYPE_NULL;
    new->value.as_ptr = NULL;
    return new;
}

void jval_destroy(const struct jval *self)
{
    if (self->type == JTYPE_OBJECT)
        jobj_destroy(self->value.as_ptr);
    if (self->type == JTYPE_ARRAY)
        jarr_destroy(self->value.as_ptr);
    if (self->type == JTYPE_STRING)
        free(self->value.as_ptr);
    free((void *)self);
}
