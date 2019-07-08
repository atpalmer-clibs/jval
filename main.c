#include "jobj.h"


int main(void) {
    struct jobj *obj = jobj_new();

    jobj_add_double(obj, "value", 4);
    jobj_add_double(obj, "value2", 5);

    jobj_to_console(obj);

    jobj_destroy(obj);
}
