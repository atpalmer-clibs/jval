#ifndef JOBJ_H
#define JOBJ_H


#include "jcollection.h"
#include "jarr.h"


struct jprop;


struct jobj {
    size_t count;
    size_t capacity;
    struct jprop *props;
};


struct jprop {
    const char *name;
    struct jval jval;
};


struct jobj *jobj_new(void);
void jobj_destroy(const struct jobj *self);
void jobj_to_console(struct jobj *self);
void jobj_add_long(struct jobj *self, const char *name, long value);
void jobj_add_double(struct jobj *self, const char *name, double value);
void jobj_add_string(struct jobj *self, const char *name, const char *value);
void jobj_add_jarr(struct jobj *self, const char *name, struct jarr *value);
void jobj_add_jobj(struct jobj *self, const char *name, struct jobj *value);

#endif
