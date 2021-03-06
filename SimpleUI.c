
#include "UI.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef struct UI {
  FILE *out;
  FILE *in;
} UI;

struct UI *UI_create() {
  UI *self = calloc(1, sizeof(UI));
  self->out = stdout;
  self->in = stdin;
  return self;
}

void UI_destroy(UI *self) {
  free(self);
}

void UI_printf(UI *self, const char* format, ...) {
  va_list argptr;
  va_start(argptr, format);
  vfprintf(self->out, format, argptr);
  va_end(argptr);
}

void UI_gets(UI *self, char *str, int n) {
  fgets(str, n, self->in);

  /* remove the LR from the string */
  char *c = strchr(str, 10);
  if (c)
    *c = 0;
}

char UI_key(UI *self) {
  char c = 0;
  c = fgetc(stdin);
  return c;
}

void UI_stop(UI *self) {
  /* fprintf(self->out, "\n"); */
}

void UI_csr(UI *self, int x) {
  int i;
  for (i = 0; i < x; ++i)
    fprintf(self->out, " ");
}

void UI_clear(UI *self) {
  fprintf(self->out, "\n");
}

void UI_ready(UI *self, int mode, int prog_area) {
  if (mode == 0) {
    /* It is a great pleasure to output... */
    UI_printf(self, "READY P%d", prog_area);
    UI_clear(self);
  } else {
    UI_printf(self, "P 0123456789 %d", prog_area);
    UI_clear(self);
  }
}
