#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {

  if (argc < 2) {
    std::cerr << "No arguments" << std::endl;
    return 1;
  }

  std::string input;

  if (*argv[1] == '-') {
    std::vector<std::string> strVector;

    while (std::getline(std::cin, input)) {

      strVector.push_back(input);
    }

    std::reverse(strVector.begin(), strVector.end());

    for (const auto &line : strVector) {
      std::cout << line << std::endl;
    }

  }

  else {

    for (int i = 1; i < argc; ++i) {
      std::vector<std::string> strVector;
      std::ifstream file(argv[i]);
      if (!file.is_open()) {
        std::cerr << "Failure Opening File" << std::endl;
        return 1;
      }

      while (std::getline(file, input)) {

        strVector.push_back(input);
      }

      std::reverse(strVector.begin(), strVector.end());

      for (const auto &line : strVector) {
        std::cout << line << std::endl;
      }
      file.close();

    }
  }
  return 0;
}