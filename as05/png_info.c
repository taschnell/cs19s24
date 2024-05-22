/*
 * @file png_info.c
 * A program that outputs info on the cunks of a PNG Image C
 */
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
// Uses Bitshifting to reverse the order of the bytes in a uint32_t
// Used for 4-Byte ints --> Interperted by CPU in reverse order
void invert_4bytes(uint32_t *num) {
  *num = (((*num & 0xFF) << 24) | ((*num & 0xFF00) << 8) |
          ((*num & 0xFF0000) >> 8) | ((*num & 0xFF000000) >> 24));
}
// Uses Bitshifting to reverse the order of the bytes in a uint16_t
// Used for 2-Byte ints --> Interperted by CPU in reverse order
void invert_2bytes(uint16_t *num) {
  *num = ((*num & 0xFF) << 8) | ((*num & 0xFF00) >> 8);
}

int main(int argc, char **argv) {
  FILE *file;
  uint32_t num;
  uint32_t type;
  char *chuck_name = (char *)&type;
  int verbose = 0;
  size_t bytes;
  if (strncmp(argv[1], "-v", 2) == 0) {
    file = fopen(argv[2], "rb");
    verbose = 1;
  } else {
    file = fopen(argv[1], "rb");
  }
  if (file == NULL) {
    perror("ERROR");
    return 1;
  }
  if (argc > 3) {
    printf("Too many Arguments");
    return 1;
  }
  fseek(file, 8, 0);
  while (strncmp(chuck_name, "IEND", 4) != 0) {
    // Core Function
    bytes = fread(&num, sizeof(num), 1, file);
    if (bytes == 0) {
      perror("ERROR");
      return 1;
    }
    invert_4bytes(&num);
    fseek(file, 0, bytes);
    bytes = fread(&type, sizeof(type), 1, file);
    if (file == 0) {
      perror("ERROR");
      return 1;
    }
    for (size_t i = 0; i < sizeof(type); i++) {
      printf("%c", chuck_name[i]);
    }
    printf(" (%d)\n", num);
    // Verbose functionality
    if (verbose) {
      // Verbose IHDR Management
      if (strncmp(chuck_name, "IHDR", 4) == 0) {
        uint32_t width;
        uint32_t height;
        bytes = fread(&width, sizeof(width), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }
        bytes = fread(&height, sizeof(height), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }
        invert_4bytes(&width);
        invert_4bytes(&height);

        uint8_t pixel_depth;
        bytes = fread(&pixel_depth, sizeof(pixel_depth), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }

        uint8_t pixel_type;
        bytes = fread(&pixel_type, sizeof(pixel_type), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }
        const char *type;
        switch (pixel_type) {
        case 0:
          type = "greyscale";
          break;
        case 2:
          type = "truecolour";
          break;
        case 3:
          type = "indexed-colour";
          break;
        case 4:
          type = "greyscale with alpha";
          break;
        case 6:
          type = "truecolour with alpha";
          break;
        default:
          type = "other";
        }

        uint8_t interlaced;
        bytes = fread(&interlaced, sizeof(interlaced), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }
        const char *interlace_method;
        switch (interlaced) {
        case 0:
          interlace_method = "non-interlaced";
          break;
        case 1:
          interlace_method = "interlaced";
          break;
        default:
          interlace_method = "other";
        }
        printf("%dx%d %d-bit %s %s\n", width, height, pixel_depth, type,
               interlace_method);
        fseek(file, num - 7, bytes);
      } else if (strncmp(chuck_name, "tIME", 4) == 0) {
        // Verbose tIME Management
        uint16_t year;
        uint8_t month;
        uint8_t day;
        bytes = fread(&year, sizeof(year), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }
        invert_2bytes(&year);
        bytes = fread(&month, sizeof(month), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }
        bytes = fread(&day, sizeof(day), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }

        uint8_t hour;
        uint8_t minute;
        uint8_t second;
        bytes = fread(&hour, sizeof(hour), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }
        bytes = fread(&minute, sizeof(minute), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }
        bytes = fread(&second, sizeof(second), 1, file);
        if (bytes == 0) {
          perror("ERROR");
          return 1;
        }

        printf("%d-%02d-%02d %02d:%02d:%02d\n", year, month, day, hour, minute,
               second);

        fseek(file, num - 3, bytes);

      } else if (strncmp(chuck_name, "tEXt", 4) == 0) {
        uint8_t character;
        int print = 0;
        for (uint32_t i = 1; i <= num; i++) {
          bytes = fread(&character, sizeof(character), 1, file);
          if (bytes == 0) {
            perror("ERROR");
            return 1;
          }
          if (isprint(character) != 0 && print != 2) {
            printf("%c", character);
          } else if (print == 0 && isprint(character) == 0) {
            printf("%s", ": ");
            print = 1;          } else if (print == 1 && isprint(character) == 0) {
            print = 2;
            continue;
          }
        }
        printf("%c", '\n');
        fseek(file, 4, bytes);

      } else {
        fseek(file, num + 4, bytes);
      }
    } else {
      fseek(file, num + 4, bytes);
    }
  }

  fclose(file);
  return 0;
}