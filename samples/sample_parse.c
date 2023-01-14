#include <jval.h>
#include <pthread.h>

static const char *DATA =
    "["
        "{"
            "\"city\": \"New York\","
            "\"state\": \"New York\","
            "\"temperature\": 35.2"
        "}"
    ","
        "{"
            "\"city\": \"Chicago\","
            "\"state\": \"Illinois\","
            "\"temperature\": 30"
        "}"
    "]"
    ;

void success(void)
{
    struct jval *cities = jval_parse_from_string(DATA);
    jval_out(cities, stdout);
    jval_destroy(cities);
    printf("\n");
}

void fail_1(void)
{
    printf("\nBAD CHAR: ");
    struct jval *v = jval_parse_from_string("x");
    jval_destroy(v);
}

void fail_2(void)
{
    printf("\nBAD ARRAY: ");
    struct jval *v = jval_parse_from_string("[123 456]");
    jval_destroy(v);
}

void fail_3(void)
{
    printf("\nBAD OBJECT: ");
    struct jval *v = jval_parse_from_string("{\"123\": 456,}");
    jval_destroy(v);
}

int main(void)
{
    success();
    fail_1();
    fail_2();
    fail_3();
}
