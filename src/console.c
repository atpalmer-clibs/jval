#include "jval/jval.h"
#include "jval/console.h"


static void _array_container_out(struct jval_container *self, FILE *out)
{
    fprintf(out, "[");
    if (self->count) {
        size_t curr = 0;
        for (;;) {
            jval_out(self->entries[curr], out);
            ++curr;
            if (curr == self->count)
                break;
            fprintf(out, ",");
        }
    }
    fprintf(out, "]");
}

static void _object_container_out(struct jval_container *self, FILE *out)
{
    fprintf(out, "{");
    if (self->count) {
        size_t curr = 0;
        for (;;) {
            struct jval_object_entry *entry = self->entries[curr];
            fprintf(out, "\"%s\":", entry->name);
            jval_out(entry->value, out);
            ++curr;
            if (curr == self->count)
                break;
            fprintf(out, ",");
        }
    }
    fprintf(out, "}");
}

void jval_out(struct jval *self, FILE *out)
{
    switch (self->type) {
    case JVAL_TP_INTEGER:
        fprintf(out, "%ld", self->value.as_long);
        break;
    case JVAL_TP_NUMBER:
        fprintf(out, "%f", self->value.as_double);
        break;
    case JVAL_TP_BOOL:
        fprintf(out, "%s", self->value.as_bool ? "true" : "false");
        break;
    case JVAL_TP_STRING:
        fprintf(out, "\"%s\"", self->value.as_string);
        break;
    case JVAL_TP_ARRAY:
        _array_container_out(self->value.as_container, out);
        break;
    case JVAL_TP_OBJECT:
        _object_container_out(self->value.as_container, out);
        break;
    case JVAL_TP_NULL:
        fprintf(out, "null");
        break;
    };
}

void jval_to_console(struct jval *self)
{
    jval_out(self, stdout);
}
