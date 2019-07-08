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


struct jobj {
    size_t count;
    size_t capacity;
    struct jprop *props;
};


struct jval {
    enum jtype type;
    union {
        void *as_ptr;
        struct jobj *as_jobj;
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

#endif
