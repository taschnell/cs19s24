/*
 *@rosalind_gc.c
 * Rosalind_DNA in C
 */
#include <stdio.h>
int main(void) {
  float acgt = 0, cg = 0, output = 0;

  for (int character = getchar(); character != EOF; character = getchar()) {
    switch (character) {
    case 'A':
      ++acgt;
      break;
    case 'C ':
      ++acgt;
      ++cg;
      break;
    case 'G':
      ++acgt;
      ++cg;
      break;
    case 'T':
      ++acgt;
      break;
    }
  }
  if (cg != 0 || acgt != 0) {
    output = cg / acgt * 100;
  }
  printf("%f\n", output);
  return 0;
}