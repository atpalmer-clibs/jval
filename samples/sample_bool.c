#include <jval.h>

static struct jval *create_bool_array(void)
{
    struct jval *boolarr = jval_new_array();

    /* four equivalent ways to append a bool to an array: */

    /* 1.) create bool jvals */
    jval_append(boolarr, jval_from_bool(1));
    jval_append(boolarr, jval_from_bool(0));

    /* 2.) append bool singletons */
    jval_append(boolarr, &jval_true);
    jval_append(boolarr, &jval_false);

    /* 3.) use append bool shortcuts */
    jval_append_true(boolarr);
    jval_append_false(boolarr);

    /* 4.) use append_bool */
    jval_append_bool(boolarr, 1);
    jval_append_bool(boolarr, 0);

    return boolarr;
}

static struct jval *create_bool_object(void)
{
    struct jval *boolobj = jval_new_object();

    /* four equivalent ways to set a bool on an object: */

    /* 1.) create bool jvals */
    jval_set(boolobj, "trueJvalFromBool", jval_from_bool(1));
    jval_set(boolobj, "falseJvalFromBool", jval_from_bool(0));

    /* 2.) set bool singletons */
    jval_set(boolobj, "trueSingleton", &jval_true);
    jval_set(boolobj, "falseSingleton", &jval_false);

    /* 3.) use set bool shortcuts */
    jval_set_true(boolobj, "trueShortcut");
    jval_set_false(boolobj, "falselShortcut");

    /* 4.) use set_bool */
    jval_set_bool(boolobj, "trueSetBool", 1);
    jval_set_bool(boolobj, "falseSetBool", 0);

    return boolobj;
}

int main(void)
{
    struct jval *boolarr = create_bool_array();
    struct jval *boolobj = create_bool_object();

    /* add array to object */
    jval_set(boolobj, "boolArray", boolarr);

    /* output object JSON to console */
    jval_out(boolobj, stdout);

    /* call destroy on top level jval only */
    jval_destroy(boolobj);
}
