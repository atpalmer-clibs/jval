#include "jtypes/jtypes.h"


void jarr_destroy(const struct jarr *self)
{
    for (size_t i = 0; i < self->count; ++i)
        jval_destroy(self->entries[i]);
    free((void *)self);
}

void jarr_add_long(struct jarr **self, long value)
{
    struct jval *jval = jval_from_long(value);
    jcollection_add_entry((struct jcollection **)self, jval);
}

void jarr_add_double(struct jarr **self, double value)
{
    struct jval *jval = jval_from_double(value);
    jcollection_add_entry((struct jcollection **)self, jval);
}

void jarr_add_bool(struct jarr **self, int value)
{
    struct jval *jval = jval_from_bool(value);
    jcollection_add_entry((struct jcollection **)self, jval);
}

void jarr_add_string(struct jarr **self, const char *value)
{
    if (!value) {
        jarr_add_null(self);
        return;
    }
    struct jval *jval = jval_from_string(value);
    jcollection_add_entry((struct jcollection **)self, jval);
}

void jarr_add_jarr(struct jarr **self, struct jarr *value)
{
    if (!value) {
        jarr_add_null(self);
        return;
    }
    struct jval *jval = jval_from_jarr(value);
    jcollection_add_entry((struct jcollection **)self, jval);
}

void jarr_add_jobj(struct jarr **self, struct jobj *value)
{
    if (!value) {
        jarr_add_null(self);
        return;
    }
    struct jval *jval = jval_from_jobj(value);
    jcollection_add_entry((struct jcollection **)self, jval);
}

void jarr_add_null(struct jarr **self)
{
    struct jval *jval = jval_new_null();
    jcollection_add_entry((struct jcollection **)self, jval);
}
