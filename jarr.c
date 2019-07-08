#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jarr.h"
#include "jcollection.h"


static struct jval *jarr_new_val(struct jarr *self) {
    struct jval *new_val = jcollection_new_entry((struct jcollection *)self, sizeof *self->vals);
    return new_val;
}


struct jarr *jarr_new(void) {
    struct jarr *new = (struct jarr *)jcollection_new(sizeof *new->vals);
    return new;
}


void jarr_destroy(const struct jarr *self) {
    for(int i = 0; i < self->count; ++i) {
        jval_cleanup(&self->vals[i]);
    }
    free((void *)self->vals);
    free((void *)self);
}


void jarr_to_console(struct jarr *self) {
    for(int i = 0; i < self->count; ++i) {
        jval_to_console(&self->vals[i]);
        printf("\n");
    }
}


void jarr_add_long(struct jarr *self, long value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_INTEGER;
    new_val->value.as_long = value;
}


void jarr_add_double(struct jarr *self, double value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_NUMBER;
    new_val->value.as_double = value;
}


void jarr_add_string(struct jarr *self, const char *value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_STRING;
    new_val->value.as_string = strdup(value);
}


void jarr_add_jarr(struct jarr *self, struct jarr *value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_ARRAY;
    new_val->value.as_jarr = value;
}


void jarr_add_jobj(struct jarr *self, struct jobj *value) {
    struct jval *new_val = jarr_new_val(self);
    new_val->type = JTYPE_OBJECT;
    new_val->value.as_jobj = value;
}