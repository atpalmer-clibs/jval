#ifndef JTYPES_CONSOLE_H
#define JTYPES_CONSOLE_H

#include "jtypes.h"

static void jval_to_console(struct jval *self);

static void jarr_to_console(struct jarr *self)
{
    printf("[");
    if (self->count) {
        size_t curr = 0;
        for (;;) {
            jval_to_console(self->entries[curr]);
            ++curr;
            if (curr == self->count)
                break;
            printf(",");
        }
    }
    printf("]");
}

static void jobj_to_console(struct jobj *self)
{
    printf("{");
    if (self->count) {
        size_t curr = 0;
        for (;;) {
            struct jobj_entry *entry = self->entries[curr];
            printf("\"%s\":", entry->name);
            jval_to_console(entry->value);
            ++curr;
            if (curr == self->count)
                break;
            printf(",");
        }
    }
    printf("}");
}

static void jval_to_console(struct jval *self)
{
    if (self->type == JTYPE_INTEGER)
        printf("%ld", self->value.as_long);
    if (self->type == JTYPE_NUMBER)
        printf("%f", self->value.as_double);
    if (self->type == JTYPE_BOOL)
        printf("%s", self->value.as_bool ? "true" : "false");
    if (self->type == JTYPE_STRING)
        printf("\"%s\"", self->value.as_string);
    if (self->type == JTYPE_ARRAY)
        jarr_to_console(self->value.as_jarr);
    if (self->type == JTYPE_OBJECT)
        jobj_to_console(self->value.as_jobj);
    if (self->type == JTYPE_NULL)
        printf("null");
}

#endif
