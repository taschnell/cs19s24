/*
 *@rosalind_gc.c
 * Rosalind_DNA_2 in C
 */
#include <stdio.h>
#define BUFFER_SIZE 8192
int main(void) {
  float output = 0;
  int bases[2] = {0};
  char buffer[BUFFER_SIZE];
  for (int fill_amount = fread(buffer, 1, BUFFER_SIZE, stdin); fill_amount;
       fill_amount = fread(buffer, 1, BUFFER_SIZE, stdin)) {
    for (int i = 0; i < fill_amount; ++i) {
      switch (buffer[i]) {
      case 'A':
        ++bases[0];
        break;
      case 'C':
        ++bases[1];
        ++bases[0];
        break;
      case 'G':
        ++bases[1];
        ++bases[0];
        break;
      case 'T':
        ++bases[0];
        break;
      }
    }
  }
  if (bases[1] != 0 || bases[0] != 0) {
    output = (float)bases[1] / (float)bases[0] * 100;
  }
  printf("%f\n", output);
  return 0;
}