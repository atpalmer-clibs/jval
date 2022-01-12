#include "jtypes/jtypes.h"


typedef void (*entry_destroy_func)(void *);

static void jval_object_entry_destroy(struct jval_object_entry *entry)
{
    free((void *)entry->name);
    jval_destroy(entry->value);
}

static void jval_container_destroy(struct jval_container *self, entry_destroy_func entry_destroy)
{
    for (size_t i = 0; i < self->count; ++i)
        entry_destroy(self->entries[i]);
    free(self);
}

static void jval_object_container_destroy(struct jval_container *self)
{
    jval_container_destroy(self, (entry_destroy_func)jval_object_entry_destroy);
}

static void jval_array_container_destroy(struct jval_container *self)
{
    jval_container_destroy(self, (entry_destroy_func)jval_destroy);
}

static struct jval_container *jval_container_new(void)
{
    static const size_t INITIAL_CAPACITY = 1;
    struct jval_container *new = malloc(sizeof *new + (INITIAL_CAPACITY * sizeof new->entries[0]));
    new->count = 0;
    new->capacity = INITIAL_CAPACITY;
    return new;
}

static void jval_container_append(struct jval_container **self, void *entry)
{
    while ((*self)->count >= (*self)->capacity) {
        size_t new_cap = (*self)->capacity * 2;
        *self = realloc(*self, sizeof **self + (new_cap * sizeof((*self)->entries[0])));
        (*self)->capacity = new_cap;
    }

    (*self)->entries[(*self)->count] = entry;
    ++(*self)->count;
}

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
