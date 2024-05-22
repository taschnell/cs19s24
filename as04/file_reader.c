/*
 *@file_reader.c
 * File_Reader in C
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {

  FILE *element_data;
  char ch;

  element_data = fopen(argv[1], "r");

  if (element_data == NULL) {
    perror("Failed To Open File");
    return EXIT_FAILURE;
  }

  do {
    ch = fgetc(element_data);
    printf("%c", ch);

  } while (ch != EOF);

  fclose(element_data);

  return 0;
}
