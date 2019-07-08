#ifndef JCOLLECTION_H
#define JCOLLECTION_H


#include <stdlib.h>
#include "jtype.h"


struct jval {
    enum jtype type;
    union {
        void *as_ptr;
        struct jobj *as_jobj;
        struct jarr *as_jarr;
        const char *as_string;
        long as_long;
        double as_double;
    } value;
};


struct jcollection {
    size_t count;
    size_t capacity;
    void *entries;
};


struct jcollection *jcollection_new(size_t entry_size);
void *jcollection_new_entry(struct jcollection *self, size_t entry_size);
void jval_cleanup(const struct jval *self);
void jval_to_console(struct jval *self);

#endif
