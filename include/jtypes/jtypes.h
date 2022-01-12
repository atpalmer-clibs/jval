#ifndef JTYPES_H
#define JTYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum jtype {
    JTYPE_INTEGER,
    JTYPE_NUMBER,
    JTYPE_STRING,
    JTYPE_ARRAY,
    JTYPE_OBJECT,
    JTYPE_BOOL,
    JTYPE_NULL,
};

/*
 * jval struct represents any (JSON) value
 * types have a corresponding union member
 *
 * jval.type        jval.value
 * JTYPE_INTEGER    .as_long
 * JTYPE_NUMBER     .as_double
 * JTYPE_STRING     .as_string
 * JTYPE_ARRAY      .as_container
 * JTYPE_OBJECT     .as_container
 * JTYPE_BOOL       .as_bool
 * JTYPE_NULL       <n/a>
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


/*
 * jval_container provides support for container types
 * (allocated on jval.value.as_container for arrays and objects)
 * - "arrays" have jval entries
 * - "objects" have jval_object_entry entries
 *   (note: duplicate key names permitted)
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


/*
 * aborts on failure, returns self on success
 */
struct jval *jval_ensure_type(struct jval *self, enum jtype type);

/*
 * append requires array, aborts on failure
 * array steals ownership of value
 */
void jval_append(struct jval *self, struct jval *value);

/*
 * set requires object, aborts on failure
 * object steals ownership of value
 */
void jval_set(struct jval *self, const char *name, struct jval *value);

/*
 * create jvals of any type
 * - c long -> JTYPE_INTEGER
 * - c double -> JTYPE_NUMBER
 * - c bool -> JTYPE_BOOL
 * - c string -> JTYPE_STRING
 * - empty JTYPE_ARRAY (append with jval_append)
 * - empty JTYPE_OBJECT (set with jval_set)
 * - JTYPE_NULL
 */
struct jval *jval_from_long(long value);
struct jval *jval_from_double(double value);
struct jval *jval_from_bool(int value);
struct jval *jval_from_string(const char *value);
struct jval *jval_new_array(void);
struct jval *jval_new_object(void);
struct jval *jval_new_null(void);

/*
 * destroy any jval recursively
 */
void jval_destroy(struct jval *self);

#endif
