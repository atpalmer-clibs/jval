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
    JTYPE_INTEGER = 1 << 0,
    JTYPE_NUMBER = 1 << 1,
    JTYPE_STRING = 1 << 2,
    JTYPE_ARRAY = 1 << 3,
    JTYPE_OBJECT = 1 << 4,
    JTYPE_BOOL = 1 << 5,
    JTYPE_NULL = 1 << 6,
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

struct jval_container *jval_container_new(void);
void jval_container_append(struct jval_container **self, void *entry);

void jval_array_container_destroy(struct jval_container *self);
void jval_object_container_destroy(struct jval_container *self);

#endif
