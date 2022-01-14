#include "jval/jval.h"
#include "jval/console.h"


int main(void)
{
    struct jval *nested_obj = jval_new_object();
    jval_set(nested_obj, "city", jval_from_string("Chicago"));
    jval_set(nested_obj, "state", jval_from_string("Illinois"));

    struct jval *obj = jval_new_object();

    jval_set(obj, "value", jval_from_double(4));
    jval_set(obj, "value2", jval_from_double(5));
    jval_set(obj, "name", jval_from_string("Andy"));
    jval_set(obj, "int-value", jval_from_long(6));

    struct jval *nested_arr = jval_new_array();
    jval_append(nested_arr, jval_from_string("1"));
    jval_append(nested_arr, jval_from_string("0"));
    jval_append(nested_arr, jval_from_string("4"));

    struct jval *arr_obj = jval_new_object();
    jval_set(arr_obj, "value", jval_from_double(105));

    struct jval *bool_arr = jval_new_array();
    jval_append(bool_arr, jval_from_bool(1));
    jval_append(bool_arr, jval_from_bool(0));

    struct jval *arr = jval_new_array();
    jval_append(arr, jval_from_long(100));
    jval_append(arr, jval_from_double(101));
    jval_append(arr, jval_from_string("0102"));
    jval_append(arr, jval_from_double(103));
    jval_append(arr, nested_arr);
    jval_append(arr, arr_obj);
    jval_append(arr, bool_arr);
    jval_append(arr, jval_new_null());
    jval_append(arr, NULL);

    jval_set(obj, "myArray", arr);
    jval_set(obj, "location", nested_obj);

    jval_set(obj, "true", &jval_true);
    jval_set(obj, "false", &jval_false);

    jval_set(obj, "oneNull", NULL);
    jval_set(obj, "twoNull", &jval_null);

    char *json = jval_to_json(obj, NULL);
    printf("%s\n", json);
    free(json);

    jval_destroy(obj);
}
