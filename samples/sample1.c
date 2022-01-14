#include <jval.h>

int main(void)
{
    struct jval *nested_obj = jval_new_object();
    jval_set(nested_obj, "city", jval_from_string("Chicago"));
    jval_set_string(nested_obj, "state", "Illinois");

    struct jval *obj = jval_new_object();

    jval_set(obj, "value", jval_from_double(4));
    jval_set_double(obj, "value2", 5);
    jval_set_string(obj, "name", "Andy");
    jval_set(obj, "int-value", jval_from_long(6));

    struct jval *nested_arr = jval_new_array();
    jval_append_string(nested_arr, "1");
    jval_append_string(nested_arr, "0");
    jval_append_string(nested_arr, "4");

    struct jval *arr_obj = jval_new_object();
    jval_set_double(arr_obj, "value", 105);

    struct jval *bool_arr = jval_new_array();
    jval_append(bool_arr, jval_from_bool(1));
    jval_append_bool(bool_arr, 0);

    struct jval *arr = jval_new_array();
    jval_append_long(arr, 100);
    jval_append_double(arr, 101);
    jval_append_string(arr, "0102");
    jval_append_double(arr, 103);
    jval_append(arr, nested_arr);
    jval_append(arr, arr_obj);
    jval_append(arr, bool_arr);
    jval_append(arr, jval_new_null());
    jval_append(arr, NULL);

    jval_set(obj, "myArray", arr);
    jval_set(obj, "location", nested_obj);

    jval_set(obj, "true", &jval_true);
    jval_set_false(obj, "false");

    jval_set_null(obj, "oneNull");
    jval_set(obj, "twoNull", &jval_null);

    char *json = jval_to_json(obj, NULL);
    printf("%s\n", json);
    free(json);

    jval_destroy(obj);
}
