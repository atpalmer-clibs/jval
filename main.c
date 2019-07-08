#include "jobj.h"


int main(void) {
    struct jobj *obj = jobj_new();

    jobj_add_double(obj, "value", 4);
    jobj_add_double(obj, "value2", 5);
    jobj_add_string(obj, "name", "Andy");
    jobj_add_long(obj, "int-value", 6);

    struct jarr *arr = jarr_new();
    jarr_add_long(arr, 100);
    jarr_add_long(arr, 101);
    jarr_add_long(arr, 102);
    jarr_add_long(arr, 103);

    jobj_add_jarr(obj, "myArray", arr);

    jobj_to_console(obj);

    jobj_destroy(obj);
}
