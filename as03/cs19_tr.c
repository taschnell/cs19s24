/*
 *@cs19_tr.c
 * the tr utility C
 */
#include "cs19_python_strings.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
  char *from = argv[1];
  char *to = argv[2];
  char *buffer = NULL;
  size_t read;
  size_t bufsize = 0;

  while (getline(&buffer, &bufsize, stdin) != -1) {
    char *translated = cs19_str_translate(buffer, from, to);
    printf("%s", translated);
    free(translated);
  }
  free(buffer);
}