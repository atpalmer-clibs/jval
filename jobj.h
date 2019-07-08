#ifndef JOBJ_H
#define JOBJ_H


#include "jtype.h"
#include "jcollection.h"


struct jprop;


struct jobj {
    size_t count;
    size_t capacity;
    struct jprop *props;
};


struct jarr {
    size_t count;
    size_t capacity;
    struct jval *vals;
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

struct jarr *jarr_new(void);
void jarr_destroy(const struct jarr *self);
void jarr_to_console(struct jarr *self);
void jarr_add_long(struct jarr *self, long value);
void jarr_add_double(struct jarr *self, double value);
void jarr_add_string(struct jarr *self, const char *value);
void jarr_add_jarr(struct jarr *self, struct jarr *value);
void jarr_add_jobj(struct jarr *self, struct jobj *value);

#endif
