#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
// Uses Bitshifting to reverse the order of the bytes in a uint16_t
// Used for 2-Byte ints --> Interperted by CPU in reverse order due to Big
// Endianess
void invert_2bytes(uint16_t *num) {
  *num = ((*num & 0xFF) << 8) | ((*num & 0xFF00) >> 8);
}

int main(int argc, char **argv) {
  if (argc == 1) {
    perror("No Argument -- Specify Big or Little Endian");
    return 1;
  }

  int big_end = 0;
  if (std::strncmp(argv[1], "big", 3) == 0) {
    big_end = 1;
  }

  char out = 0;
  int bit = 7;
  while (std::cin) {
    uint16_t sample;
    std::cin.read(reinterpret_cast<char *>(&sample), 2);
    // Read in 2 bytes (16 Bits)
    if (big_end) {
      invert_2bytes(&sample);
    }
    out |= (sample & 1) << bit;
    bit--;

    if (bit < 0) {
      if (out == '\0') {
        break;
      }
      std::cout << out;
      out = 0;
      bit = 7;
    }
  }
  return 0;
}