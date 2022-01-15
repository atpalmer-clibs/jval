#include <jval.h>
#include <string.h>

int main(void)
{
    /* create some jval */
    struct jval *obj = jval_new_object();
    jval_set_long(obj, "long", 123);
    jval_set_double(obj, "double", 123.45);
    jval_set_string(obj, "string", "one-two-three");
    jval_set_true(obj, "bool");
    jval_set_null(obj, "null");

    /* convert jval to JSON string */
    size_t len;  /* capture string length */
    char *json = jval_to_json(obj, &len);

    /* Passing NULL for length parameter is OK if not needed */
    char *newjson = jval_to_json(obj, NULL);

    /* destroy jval when we are done */
    jval_destroy(obj);

    /* use any string/memory functions on generated JSON */
    if (strcmp(json, newjson) != 0)
        exit(-1);  /* expect OK! */
    if (memcmp(json, newjson, len) != 0)
        exit(-1);  /* expect OK! */
    if (strlen(json) != len || strlen(newjson) != len)
        exit(-1);  /* expect OK! */
    if (json == newjson)
        exit(-1);  /* Still OK: multiple jval_to_json calls...
                    * generate strings that compare as equal,
                    * but are allocated separately */

    /* use length and/or '\0'-terminated JSON string */
    printf("Pointer: %p, Length: %lu, JSON: %s\n", (void *)json, len, json);
    printf("Pointer: %p, JSON: %s\n", (void *)newjson, newjson);

    /* free any generated JSON strings! */
    free(json);
    free(newjson);
}
