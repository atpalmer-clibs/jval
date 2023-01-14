#include <jval.h>

static int stream_peek(FILE *stream)
{
    int c = fgetc(stream);
    ungetc(c, stream);
    return c;
}

static int stream_expect(FILE *stream, int ex)
{
    int c = fgetc(stream);
    if (c != ex) {
        ungetc(c, stream);
        return 0;
    }
    return 1;
}

static void stream_expect_or_die(FILE *stream, int ex)
{
    if (!stream_expect(stream, ex)) {
        long pos = ftell(stream);
        char act = stream_peek(stream);
        fprintf(stderr, "stream_expect error at pos %ld: expected: '%c'; actual: '%c'.", pos, ex, act);
        exit(-1);
    }
}

static void stream_ignore_whitespace(FILE *stream)
{
    static const char WHITESPACE_CHARS[] = " \t\r\n";
    for (;;) {
        int c = fgetc(stream);
        if (!strchr(WHITESPACE_CHARS, c)) {
            ungetc(c, stream);
            return;
        }
    }
}

struct string {
    size_t cap;
    size_t size;
    char value[];
};

struct string *string_new(void)
{
    static const size_t INIT_CAP = 2;
    struct string *new = malloc(sizeof *new + (INIT_CAP * sizeof(char)));
    new->cap = INIT_CAP;
    new->size = 0;
    new->value[0] = '\0';
    return new;
}

struct string *string_append_char(struct string **self, char c)
{
    if ((*self)->cap < (*self)->size - 2) {
        size_t newcap = (*self)->cap * 2;
        struct string *tmp = realloc(*self, sizeof *tmp + (newcap * sizeof(char)));
        if (!tmp)
            goto fail;
        tmp->cap = newcap;
        *self = tmp;
    }
    (*self)->value[(*self)->size++] = c;
    (*self)->value[(*self)->size] = '\0';
    return *self;

fail:
    return NULL;
}

void string_destroy(struct string *self)
{
    free(self);
}

struct string *stream_quoted_string(FILE *stream)
{
    struct string *result = string_new();
    stream_expect_or_die(stream, '"');
    for (;;) {
        int c = fgetc(stream);
        if (c == '\\') {
            int c = fgetc(stream);
            string_append_char(&result, c);
            continue;
        }
        if (c == '"')
            break;
        if (c == EOF)
            goto fail;
        string_append_char(&result, c);
    }
    return result;

fail:
    string_destroy(result);
    return NULL;
}

static struct jval *parse_any(FILE *stream);

static struct jval *parse_object(FILE *stream)
{
    stream_expect_or_die(stream, '{');
    struct jval *new = jval_new_object();

    for (;;) {
        stream_ignore_whitespace(stream);
        struct string *key = stream_quoted_string(stream);
        if (!key)
            goto fail;
        stream_ignore_whitespace(stream);
        if (!stream_expect(stream, ':')) {
            string_destroy(key);
            goto fail;
        }
        struct jval *value = parse_any(stream);
        if (!value) {
            string_destroy(key);
            goto fail;
        }
        jval_set(new, key->value, value);
        string_destroy(key);

        stream_ignore_whitespace(stream);
        int c = stream_peek(stream);
        if (c != ',')
            break;
        stream_expect_or_die(stream, ',');
    }

    if (!stream_expect(stream, '}'))
        goto fail;

    return new;

fail:
    jval_destroy(new);
    return NULL;
}

static struct jval *parse_array(FILE *stream)
{
    stream_expect_or_die(stream, '[');
    stream_ignore_whitespace(stream);
    struct jval *new = jval_new_array();

    for (;;) {
        struct jval *value = parse_any(stream);
        if (!value)
            goto fail;
        jval_append(new, value);

        stream_ignore_whitespace(stream);
        int c = stream_peek(stream);
        if (c != ',')
            break;
        stream_expect_or_die(stream, ',');
    }

    if (!stream_expect(stream, ']'))
        goto fail;

    return new;

fail:
    jval_destroy(new);
    return NULL;
}

static struct jval *parse_string(FILE *stream)
{
    struct string *value = stream_quoted_string(stream);
    if (!value)
        return NULL;
    struct jval *result = jval_from_string(value->value);
    string_destroy(value);
    return result;
}

static struct jval *_jval_integer_from_string(const char *s)
{
    long value;
    if (sscanf(s, "%ld", &value) <= 0)
        return NULL;
    return jval_from_long(value);
}

static struct jval *_jval_double_from_string(const char *s)
{
    double value;
    if (sscanf(s, "%lf", &value) <= 0)
        return NULL;
    return jval_from_double(value);
}

static struct jval *_jval_number_from_string(const char *s)
{
    return strchr(s, '.')
        ? _jval_double_from_string(s)
        : _jval_integer_from_string(s);
}

static struct jval *parse_number(FILE *stream)
{
    static const char NUMCHARS[] = "0123456789.-";
    struct string *number = string_new();
    for (;;) {
        int c = stream_peek(stream);
        if (!strchr(NUMCHARS, c))
            break;
        stream_expect_or_die(stream, c);
        string_append_char(&number, c);
    }
    struct jval *result = _jval_number_from_string(number->value);
    string_destroy(number);

    return result;
}

static struct jval *parse_any(FILE *stream)
{
    stream_ignore_whitespace(stream);
    int c = stream_peek(stream);
    switch (c) {
    case '{':
        return parse_object(stream);
    case '[':
        return parse_array(stream);
    case '"':
        return parse_string(stream);
    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return parse_number(stream);
    default:
        return NULL;
    }
}

struct jval *jval_parse_from_stream(FILE *stream)
{
    struct jval *result = parse_any(stream);
    if (!result) {
        long pos = ftell(stream);
        int c = stream_peek(stream);
        fprintf(stderr, "Error: Invalid character at pos %ld: ", pos);
        if (c == EOF)
            fprintf(stderr, "EOF <%d>", c);
        else
            fprintf(stderr, "'%c' <%d>", c, c);
        fprintf(stderr, "\n");
        exit(-1);
    }
    return result;
}

struct jval *jval_parse_from_string(const char *string)
{
    FILE *stream = fmemopen((void *)string, strlen(string), "r");
    struct jval *result = jval_parse_from_stream(stream);
    fclose(stream);
    return result;
}
