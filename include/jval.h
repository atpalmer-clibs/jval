#ifndef JVAL_H
#define JVAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum jval_type {
    JVAL_TP_INTEGER,
    JVAL_TP_NUMBER,
    JVAL_TP_STRING,
    JVAL_TP_ARRAY,
    JVAL_TP_OBJECT,
    JVAL_TP_BOOL,
    JVAL_TP_NULL,
};

/*
 * jval struct represents any (JSON) value
 * types have a corresponding union member
 *
 * jval.type        jval.value
 * JVAL_TP_INTEGER  .as_long
 * JVAL_TP_NUMBER   .as_double
 * JVAL_TP_STRING   .as_string
 * JVAL_TP_ARRAY    .as_container
 * JVAL_TP_OBJECT   .as_container
 * JVAL_TP_BOOL     .as_bool
 * JVAL_TP_NULL     <n/a>
 */

struct jval {
    enum jval_type type;
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
 * create jvals of any type
 * - c long -> JVAL_TP_INTEGER
 * - c double -> JVAL_TP_NUMBER
 * - c bool -> JVAL_TP_BOOL
 * - c string -> JVAL_TP_STRING
 * - empty JVAL_TP_ARRAY (append with jval_append)
 * - empty JVAL_TP_OBJECT (set with jval_set)
 * - JVAL_TP_NULL
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

/* singletons */
extern struct jval jval_true;
extern struct jval jval_false;
extern struct jval jval_null;

/*
 * aborts on failure, returns self on success
 */
struct jval *jval_ensure_type(struct jval *self, enum jval_type type);

/*
 * append requires array, aborts on failure
 * array steals ownership of value
 */
void jval_append(struct jval *self, struct jval *value);

/*
 * append convenience methods
 */
static inline void jval_append_long(struct jval *self, long value)
{
    jval_append(self, jval_from_long(value));
}

static inline void jval_append_double(struct jval *self, double value)
{
    jval_append(self, jval_from_double(value));
}

static inline void jval_append_bool(struct jval *self, int value)
{
    jval_append(self, jval_from_bool(value));
}

static inline void jval_append_string(struct jval *self, const char *value)
{
    jval_append(self, jval_from_string(value));
}

static inline void jval_append_true(struct jval *self)
{
    jval_append(self, &jval_true);
}

static inline void jval_append_false(struct jval *self)
{
    jval_append(self, &jval_false);
}

static inline void jval_append_null(struct jval *self)
{
    jval_append(self, &jval_null);
}

/*
 * set requires object, aborts on failure
 * object steals ownership of value
 */
void jval_set(struct jval *self, const char *name, struct jval *value);

/*
 * set convenience methods
 */
static inline void jval_set_long(struct jval *self, const char *name, long value)
{
    jval_set(self, name, jval_from_long(value));
}

static inline void jval_set_double(struct jval *self, const char *name, double value)
{
    jval_set(self, name, jval_from_double(value));
}

static inline void jval_set_bool(struct jval *self, const char *name, int value)
{
    jval_set(self, name, jval_from_bool(value));
}

static inline void jval_set_string(struct jval *self, const char *name, const char *value)
{
    jval_set(self, name, jval_from_string(value));
}

static inline void jval_set_true(struct jval *self, const char *name)
{
    jval_set(self, name, &jval_true);
}

static inline void jval_set_false(struct jval *self, const char *name)
{
    jval_set(self, name, &jval_false);
}

static inline void jval_set_null(struct jval *self, const char *name)
{
    jval_set(self, name, &jval_null);
}

/* output JSON to FILE * or char * */
void jval_out(struct jval *self, FILE *out);
char *jval_to_json(struct jval *self, size_t *jsonlen);

/*
 * Parse methods
 */
struct jval *jval_parse_from_stream(FILE *stream);
struct jval *jval_parse_from_string(const char *string);

#endif
