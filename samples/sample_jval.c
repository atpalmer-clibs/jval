#include <jval.h>

int main(void)
{
    /* create jvals from various c types */
    struct jval *jlong = jval_from_long(123);
    struct jval *jdouble = jval_from_double(123.45);
    struct jval *jstring = jval_from_string("one-two-three");
    struct jval *jbool = jval_from_bool(1);

    struct jval *not_used = jval_from_long(123);
    jval_destroy(not_used); /* cleanup jvals when done */

    struct jval *jobj = jval_new_object();

    jval_set(jobj, "long", jlong);      /* jlong is owned by obj */
    jval_set(jobj, "double", jdouble);  /* jdouble is owned by obj */
    jval_set(jobj, "string", jstring);  /* jstring is owned by obj */
    jval_set(jobj, "bool", jbool);      /* jbool is owned by obj */

    jval_out(jobj, stdout);

    jval_destroy(jobj); /* destroys all jvals owned by jobj */
}
