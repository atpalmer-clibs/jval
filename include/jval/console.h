#ifndef JVAL_CONSOLE_H
#define JVAL_CONSOLE_H

void jval_out(struct jval *self, FILE *out);
char *jval_to_json(struct jval *self, size_t *jsonlen);

#endif
