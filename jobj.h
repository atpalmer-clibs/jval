#ifndef JOBJ_H
#define JOBJ_H


#include <stdlib.h>


enum jtype {
    JTYPE_INTEGER = 1 << 0,
    JTYPE_NUMBER = 1 << 1,
    JTYPE_STRING = 1 << 2,
    JTYPE_ARRAY = 1 << 3,
    JTYPE_OBJECT = 1 << 4,
};


struct jprop;
struct jval;


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

struct jarr *jarr_new(void);
void jarr_destroy(const struct jarr *self);
void jarr_to_console(struct jarr *self);
void jarr_add_long(struct jarr *self, long value);
void jarr_add_double(struct jarr *self, double value);
void jarr_add_string(struct jarr *self, const char *value);
void jarr_add_jarr(struct jarr *self, struct jarr *value);

#endif
