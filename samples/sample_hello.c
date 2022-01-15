#include <jval.h>

int main(void)
{
    struct jval *obj = jval_new_object();

    jval_set_string(obj, "message", "Hello");
    jval_set_string(obj, "name", "World");

    jval_out(obj, stdout);
    /* outputs:
     *   {
     *     "message": "Hello",
     *     "name": "World"
     *   }
     */

    jval_destroy(obj);
}
