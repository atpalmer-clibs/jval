#ifndef JTYPES_H
#define JTYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*** jtype ***/
/*
 * Type specification for jval
 */

enum jtype {
    JTYPE_INTEGER,
    JTYPE_NUMBER,
    JTYPE_STRING,
    JTYPE_ARRAY,
    JTYPE_OBJECT,
    JTYPE_BOOL,
    JTYPE_NULL,
};


/*** jval ***/
/*
 * Generic JSON value of any type
 */

struct jval {
    enum jtype type;
    union {
        struct jval_container *as_container;
        const char *as_string;
        long as_long;
        double as_double;
        int as_bool;
    } value;
};


/*** jval_container ***/
/*
 * Supports arrays (jval entries) and objects (jval_object_entry entries)
 */

struct jval_object_entry {
    const char *name;
    struct jval *value;
};

struct jval_container {
    size_t count;
    size_t capacity;
    void *entries[];
};


struct jval *jval_ensure_type(struct jval *self, enum jtype type);

void jval_append(struct jval *self, struct jval *value);
void jval_set(struct jval *self, const char *name, struct jval *value);

struct jval *jval_from_long(long value);
struct jval *jval_from_double(double value);
struct jval *jval_from_bool(int value);
struct jval *jval_from_string(const char *value);
struct jval *jval_new_array(void);
struct jval *jval_new_object(void);
struct jval *jval_new_null(void);

void jval_destroy(struct jval *self);

#endif
