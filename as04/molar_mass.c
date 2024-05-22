/*
 *@molar_mass.c
 * A Molar Mass caculator  or in C
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *element_data;
  int i = 1;
  int i2 = 1;
  double total_mass = 0;

  // File Handeling
  element_data = fopen("/srv/datasets/elements", "r");

  // Building Arrays for Caculations
  char element_symbol[118][2];
  double element_mass[118];
  char line[40];

  for (int i = 0; i < 118; i++) {
    char *_ = fgets(line, sizeof(line), element_data);
    // Processing of each line
    int j = 0;
    for (int z = 0; line[z] != '\0'; z++) {
      if (line[z] == ' ') {
        j++;
        z++;
      }
      if (j == 1) {
        element_symbol[i][0] = line[z];
        z++;
        element_symbol[i][1] = line[z];
        j++;
      } else if (j > 1) {
        break;
      }
    }
    double dub;
    char *endptr;
    char *temp_line = line + 4;

    for (; *temp_line != '\0'; temp_line++) {
      dub = strtod(temp_line, &endptr);
      if (dub != 0.00) {
        element_mass[i] = dub;
        break;
      }
    }
  }
  FILE *molar_mass;

  molar_mass = fopen("molar_masses.txt", "a+");

  // Handling the Argments
  for (; i < argc; i++) {
    // Iterate through each character in argv
    for (int j = 0; argv[i][j] != '\0'; j++) {
      char element = argv[i][j];
      unsigned int count = 1;
      char element_2 = ' ';
      if (argv[i][j + 1] != '_') {
        if (argv[i][j + 1] != 0) {
          element_2 = argv[i][j + 1];
        }
        if (isdigit(argv[i][j + 3])) {
          count = atoi(&argv[i][j + 3]);
          j = j + 3;
        }
      } else if (isdigit(argv[i][j + 2])) {

        count = atoi(&argv[i][j + 2]);
        j = j + 2;

      } else {
        element_2 = ' ';
      }

      // Find the element mass from the mass array
      for (int k = 0; k < 118; k++) {
        // printf("%c\t",element_symbol[k][1]);
        // printf("%c|",element_2);
        if (element_symbol[k][0] == element &&
            element_symbol[k][1] == element_2) {
          total_mass += element_mass[k] * count;
          break;
        }
      }
    }
  }

  // Output
  for (; i2 < (argc - 1); i2++) {
    fprintf(molar_mass, "%s ", argv[i2]);
  }
  fprintf(molar_mass, "%s", argv[i2]);

  fprintf(molar_mass, "\t%f\n", total_mass);
  printf("%f\n", total_mass);

  fclose(element_data);
  fclose(molar_mass);
  return 0;
}
