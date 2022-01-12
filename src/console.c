#include "jtypes/jtypes.h"
#include "jtypes/console.h"


static void _array_container_to_console(struct jval_container *self)
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

static void _object_container_to_console(struct jval_container *self)
{
    printf("{");
    if (self->count) {
        size_t curr = 0;
        for (;;) {
            struct jval_object_entry *entry = self->entries[curr];
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

void jval_to_console(struct jval *self)
{
    switch (self->type) {
    case JTYPE_INTEGER:
        printf("%ld", self->value.as_long);
        break;
    case JTYPE_NUMBER:
        printf("%f", self->value.as_double);
        break;
    case JTYPE_BOOL:
        printf("%s", self->value.as_bool ? "true" : "false");
        break;
    case JTYPE_STRING:
        printf("\"%s\"", self->value.as_string);
        break;
    case JTYPE_ARRAY:
        _array_container_to_console(self->value.as_container);
        break;
    case JTYPE_OBJECT:
        _object_container_to_console(self->value.as_container);
        break;
    case JTYPE_NULL:
        printf("null");
        break;
    };
}
