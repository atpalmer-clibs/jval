#include "jtypes.h"
#include "console.h"


int main(void) {
    struct jobj *nested_obj = jobj_new();
    jobj_add_string(nested_obj, "city", "Chicago");
    jobj_add_string(nested_obj, "state", "Illinois");

    struct jobj *obj = jobj_new();

    jobj_add_double(obj, "value", 4);
    jobj_add_double(obj, "value2", 5);
    jobj_add_string(obj, "name", "Andy");
    jobj_add_long(obj, "int-value", 6);

    struct jarr *nested_arr = jarr_new();
    jarr_add_string(nested_arr, "1");
    jarr_add_string(nested_arr, "0");
    jarr_add_string(nested_arr, "4");

    struct jobj *arr_obj = jobj_new();
    jobj_add_double(arr_obj, "value", 105);

    struct jarr *arr = jarr_new();
    jarr_add_long(arr, 100);
    jarr_add_double(arr, 101);
    jarr_add_string(arr, "0102");
    jarr_add_double(arr, 103);
    jarr_add_jarr(arr, nested_arr);
    jarr_add_jobj(arr, arr_obj);

    jobj_add_jarr(obj, "myArray", arr);
    jobj_add_jobj(obj, "location", nested_obj);

    jobj_to_console(obj);

    jobj_destroy(obj);
}
