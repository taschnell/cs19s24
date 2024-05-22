/*
 *@molar_mass.c
 * A Molar Mass caculator  or in C
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  int exit = 0;
  FILE *element_data;
  int i = 2;
  int i2 = 2;
  int line_count = 0;

  double total_mass = 0;

  // File Handeling
  element_data = fopen(argv[1], "r");
  if (element_data == NULL) {
    element_data = fopen("/srv/datasets/elements", "r");
    exit = 1;
    i = 1;
    i2 = 1;
  }
  // How long is the data?
  char ch = ' ';
  while (ch != EOF) {
    ch = fgetc(element_data);
    if (ch == '\n') {
      line_count++;
    }
  }
  rewind(element_data);

  // Building Arrays for Caculations
  char element_symbol[line_count][2];
  double element_mass[line_count];
  char line[40];

  for (int i = 0; i < line_count; i++) {
    fgets(line, sizeof(line), element_data);
    // Processing of each line
    int j = 0;
    int o = 0;
    for (int z = 0; line[z] != '\0'; z++) {
      char temp_double[15];
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
      int count = 1;
      char element_2 = ' ';
      if (argv[i][j + 1] != '_') {
        if (argv[i][j+1] != 0){
          element_2 = argv[i][j + 1];
        }
        
        if (isdigit(argv[i][j + 3])) {
          count = atoi(&argv[i][j + 3]);
          j = j + 3; // Skip to Digit
          
        }
      } 
        else if (isdigit(argv[i][j + 2])) {
          count = atoi(&argv[i][j + 2]);
          j = j + 2; // Skip to Digit
          
        }
        else {
        element_2 = ' ';
      }

      // Find the element mass from the mass array
      for (int k = 0; k < line_count; k++) {
        //printf("%c\t",element_symbol[k][1]);
        //printf("%c|",element_2);
        if (element_symbol[k][0] == element &&
            element_symbol[k][1] == element_2) {
          total_mass += element_mass[k] * count;
          break;
        }
      }
    }
  }

  // Output
  for (; i2 < (argc-1); i2++){
  fprintf(molar_mass,"%s ", argv[i2]);
  }
  fprintf(molar_mass,"%s", argv[i2]);
  
  fprintf(molar_mass,"\t%f\n", total_mass);
  printf("%f\n", total_mass);

  fclose(element_data);
  fclose(molar_mass);
  return exit;
}
