#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main(int argc, char **argv) {

  std::string input;
  std::string last;

  bool counting = false;
  int count = 1;

  if (argc > 1) {
    if (strncmp(argv[1], "-c", 2) == 0) {
      counting = true;
    }
  }

  while (std::getline(std::cin, input)) {

    if (input != last) {
      if (!counting && last != "") {
        std::cout << last << std::endl;

      } else if (counting && last != "") {
        std::cout << '\t'  <<count << ' ' << last << std::endl;
      }

      count = 1;
    } else {
      ++count;
    }
    last = input;
  }

  if (!counting) {
    std::cout << last << std::endl;

  } else if (counting) {
    std::cout << '\t' << count << ' ' << last << std::endl;
  }

  return 0;
}