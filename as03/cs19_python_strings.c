/*
 *@cs19_python_strings.c
 * The Python String Class in C
 */

#include "cs19_python_strings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
size_t cs19_str_count_char(const char *str, char val) {
  size_t count = 0;

  while (*str != '\0') {
    if (*str == val) {
      count++;
      str++;
    } else {
      str++;
    }
  }
  return count;
}

size_t cs19_str_count_str(const char *str, const char *substr) {
  size_t count = 0;
  size_t length = strlen(substr);
  if (length == 0) {
    return strlen(str) + 1;
  }

  while (*str) {
    if (*str == *substr) {
      if (strncmp(str, substr, length) == 0) {
        count++;
        str += length;
      } else {
        str++;
      }
    } else {
      str++;
    }
  }

  return count;
}

int cs19_str_find_char(const char *str, char val) {
  int index = 0;
  while (*str != '\0') {
    if (*str == val) {
      return index;
    } else {
      index++;
    }
    str++;
  }
  return -1;
}

int cs19_str_find_str(const char *str, const char *substr) {
  int index = 0;
  size_t sub_len = strlen(substr);
  if (str == NULL || substr == NULL) {
    return 0;
  }

  if (sub_len == 0) {
    return 0;
  }

  while (*str != '\0') {
    if (strncmp(str, substr, sub_len) == 0) {
      return index;
    }
    index++;
    str++;
  }
  return -1;
}

char *cs19_str_join(const char *str, const char *sep) {
  if (strcmp(str, "") == 0) {
    return "";
  }

  int str_len = strlen(str);
  int sep_len = strlen(sep);
  size_t total_len = str_len > 0 ? (str_len - 1) * sep_len + str_len : 0;

  char *new_str = malloc(total_len + 1);
  char *pos = new_str;
  for (size_t i = 0; i < (str_len - 1); i++) {
    *pos++ = str[i];
    strcpy(pos, sep);
    pos += sep_len;
  }
  *pos++ = str[str_len - 1];
  *pos = '\0';
  return new_str;
}

char *cs19_str_strip(const char *str, const char *chars) {
  size_t str_len = strlen(str);
  size_t start = strspn(str, chars);
  size_t end = str_len - start;
  size_t stripped_len =
      end - start; // Assumed start and end are same, try again
  char *stripped_str = (char *)malloc((stripped_len + 1) * sizeof(char));

  strncpy(stripped_str, str + start, stripped_len);
  stripped_str[stripped_len] = '\0';

  return stripped_str;
}

char *cs19_str_translate(const char *str, const char *from, const char *to) {
  char *new_str = strdup(str); // Nice Function I found, just copies the string,
                               // so I have the exact right size
  if (new_str == NULL) {
    return "";
  }

  size_t from_len = strlen(from);
  size_t to_len = strlen(to);
  size_t i, j; // Index's for looping through (i: new_str), (j: from), using j
               // to allocate new characters

  for (i = 0; i < strlen(new_str); i++) {
    for (j = 0; j < from_len; j++) {
      if (new_str[i] == from[j]) {
        new_str[i] = to[j];
        break;
      }
    }
  }

  return new_str;
}
//   int str_len = strlen(str);
//   char *new_str = malloc((str_len * sizeof(char)));
//   int index = 0;
//   while (*str != '\0') {
//     int char_index = cs19_str_find_char(from, *str);
//     if (char_index != -1) {
//       new_str[index] = to[char_index];
//     }
//     if (char_index == -1) {
//       new_str[index] = *str;
//     }
//     index++;
//     str++;
//   }
//   new_str[index + 1] = '\0';
//   return new_str;
// }
// int main() {
// //   // First Function Test
// //   printf("%zu", cs19_str_count_char("appaale", 'a'));
// //   printf("%zu", cs19_str_count_char("banxxaxnex", 'x'));
// //   printf("%zu", cs19_str_count_char("apple", 'b'));

// //   // Second Function Test
// //   printf("\n");
// //   printf("%zu", cs19_str_count_str("aaaaa", "aa"));
// //   printf("\n");
// //   // Third Function test --> return 2
// //   printf("%d", cs19_str_find_char("aople", 'p'));
// //   printf("\n");

// //   // Fourth Function Test
// //   printf("%d", cs19_str_find_str("fig", ""));
// printf("%d", cs19_str_find_str("", ""));
// //   printf("\n");

// //   // Fifth Function Test
// //   printf("%d\n", strcmp(cs19_str_join("", "banana"), ""));

// //   // Sixth Function test

// printf("%s\n", cs19_str_strip("   spacious   ", " "));
// printf("%s\n", cs19_str_strip("www.example.com", "cmowz."));

// //   // Seventh Function Test
// //   printf("%s\n", cs19_str_translate("happiness", "aeiou", "xxxxx"));
// //   printf("%s\n", cs19_str_translate("rlhsjcpbnuxmpbqvgtgakp", "a",
// "u"));
//  return 0;
//   }