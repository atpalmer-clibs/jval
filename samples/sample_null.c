#include <jval.h>

static struct jval *create_null_array(void)
{
    struct jval *nullarr = jval_new_array();

    /* four equivalent ways to append null to an array: */

    /* 1.) append NULL jval */
    jval_append(nullarr, NULL);

    /* 2.) create null jval */
    jval_append(nullarr, jval_new_null());

    /* 3.) append null singleton */
    jval_append(nullarr, &jval_null);

    /* 4.) use append null shortcut */
    jval_append_null(nullarr);

    return nullarr;
}

static struct jval *create_null_object(void)
{
    struct jval *nullobj = jval_new_object();

    /* four equivalent ways to set a null on an object: */

    /* 1.) set NULL jval */
    jval_set(nullobj, "nullPtr", NULL);

    /* 2.) create null jval */
    jval_set(nullobj, "newNull", jval_new_null());

    /* 3.) set null singleton */
    jval_set(nullobj, "nullSingleton", &jval_true);

    /* 4.) use set null shortcut */
    jval_set_null(nullobj, "nullShortcut");

    return nullobj;
}

int main(void)
{
    struct jval *nullarr = create_null_array();
    struct jval *nullobj = create_null_object();

    /* add array to object */
    jval_set(nullobj, "nullArray", nullarr);

    /* output object JSON to console */
    jval_out(nullobj, stdout);

    /* call destroy on top level jval only */
    jval_destroy(nullobj);
}
