#include "jtypes/jtypes.h"


struct jval jval_true = {
    .type = JVAL_TP_BOOL,
    .value = {.as_bool = 1}
};

struct jval jval_false = {
    .type = JVAL_TP_BOOL,
    .value = {.as_bool = 0}
};

struct jval jval_null = {
    .type = JVAL_TP_NULL
};

typedef void (*entry_destroy_func)(void *);

static void _entry_destroy(struct jval_object_entry *entry)
{
    free((void *)entry->name);
    jval_destroy(entry->value);
}

static void _container_free(struct jval_container *container, entry_destroy_func entry_destroy)
{
    for (size_t i = 0; i < container->count; ++i)
        entry_destroy(container->entries[i]);
    free(container);
}

static struct jval_container *_container_alloc(void)
{
    static const size_t INITIAL_CAPACITY = 1;
    struct jval_container *new = malloc(sizeof *new + (INITIAL_CAPACITY * sizeof new->entries[0]));
    new->count = 0;
    new->capacity = INITIAL_CAPACITY;
    return new;
}

static void _container_append(struct jval_container **c, void *entry)
{
    while ((*c)->count >= (*c)->capacity) {
        size_t new_cap = (*c)->capacity * 2;
        *c = realloc(*c, sizeof **c + (new_cap * sizeof((*c)->entries[0])));
        (*c)->capacity = new_cap;
    }

    (*c)->entries[(*c)->count] = entry;
    ++(*c)->count;
}

struct jval *jval_ensure_type(struct jval *self, enum jval_type type)
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
    jval_ensure_type(self, JVAL_TP_ARRAY);
    _container_append(&self->value.as_container, jval_or_jnull(value));
}

void jval_set(struct jval *self, const char *name, struct jval *value)
{
    jval_ensure_type(self, JVAL_TP_OBJECT);

    struct jval_object_entry *new = malloc(sizeof *new);
    new->name = strdup(name);
    new->value = jval_or_jnull(value);

    _container_append(&self->value.as_container, new);
}

struct jval *jval_from_long(long value)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JVAL_TP_INTEGER;
    new->value.as_long = value;
    return new;
}

struct jval *jval_from_double(double value)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JVAL_TP_NUMBER;
    new->value.as_double = value;
    return new;
}

struct jval *jval_from_bool(int value)
{
    return value ? &jval_true : &jval_false;
}

struct jval *jval_from_string(const char *value)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JVAL_TP_STRING;
    new->value.as_string = strdup(value);
    return new;
}

struct jval *jval_new_array(void)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JVAL_TP_ARRAY;
    new->value.as_container = _container_alloc();
    return new;
}

struct jval *jval_new_object(void)
{
    struct jval *new = malloc(sizeof *new);
    new->type = JVAL_TP_OBJECT;
    new->value.as_container = _container_alloc();
    return new;
}

struct jval *jval_new_null(void)
{
    return &jval_null;
}

void jval_destroy(struct jval *self)
{
    switch (self->type) {
    case JVAL_TP_OBJECT:
        _container_free(self->value.as_container, (entry_destroy_func)_entry_destroy);
        free(self);
        break;
    case JVAL_TP_ARRAY:
        _container_free(self->value.as_container, (entry_destroy_func)jval_destroy);
        free(self);
        break;
    case JVAL_TP_STRING:
        free((void *)self->value.as_string);
        free(self);
        break;
    case JVAL_TP_NULL:
    case JVAL_TP_BOOL:
        /* do not free singletons */
        break;
    default:
        free(self);
        break;
    };
}
