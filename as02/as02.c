/*
 *@as02.c
 * Byte Histogram in C
 */

#include <ctype.h>
#include <stdio.h>

int main() {
  int terms[256] = {0};
  size_t totalBytes = 0;
  int ch;
  // Input Gathering
  while ((ch = getchar()) != EOF) {
    terms[ch]++;
    totalBytes++;
  }

  for (int i = 0; i < 256; i++) {
    if (terms[i] > 0) {
      // Print Pre Histogram
      double percentage = (double)terms[i] * 100 / totalBytes;

      printf("%03d %c %4zu %6.2f%% ", i, isprint(i) ? i : '_', terms[i],
             percentage);
      // Histogram
      for (int j = 0; j < (int)(percentage); j++) {
        printf("*");
      }
      printf("\n");
    }
  }

  return 0;
}