#ifndef JARR_H
#define JARR_H


#include "jobj.h"


struct jarr {
    size_t count;
    size_t capacity;
    struct jval *vals;
};


struct jarr *jarr_new(void);
void jarr_destroy(const struct jarr *self);
void jarr_to_console(struct jarr *self);
void jarr_add_long(struct jarr *self, long value);
void jarr_add_double(struct jarr *self, double value);
void jarr_add_string(struct jarr *self, const char *value);
void jarr_add_jarr(struct jarr *self, struct jarr *value);
void jarr_add_jobj(struct jarr *self, struct jobj *value);

#endif
