#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void loadSyllables(std::unordered_map<std::string, int> &syllables_map) {
  std::ifstream syll_file("/srv/datasets/syllables.txt");
  if (!syll_file.is_open()) {
    std::cerr << "Failed to open the file." << std::endl;
    return;
  }

  std::string line;
  int count = 1;
  while (std::getline(syll_file, line)) {
    count = 1;
    std::string key;
    int len = line.length();
    for (int i = 0; i < len; ++i) {
      if (line[i] != ';') {
        key += std::tolower(static_cast<char>(line[i]));
      } else if (line[i] == ';') {
        ++count;
      }
    }

    auto it = syllables_map.find(key);

    if (it != syllables_map.end()) {
      if (it->second < count) {
        syllables_map[key] = count;
      }
    } else {
      syllables_map[key] = count;
    }
  }
  syll_file.close();
}
void loadEasySet(std::unordered_set<std::string> &EasySet) {
  std::ifstream easy_file("/srv/datasets/dale-chall_familiar_words.txt");

  if (!easy_file.is_open()) {
    std::cerr << "Failed to open the file." << std::endl;
    return;
  }
  std::string line;
  while (std::getline(easy_file, line)) {
    for (char &c : line) {
      c = tolower(c);
    }
    EasySet.insert(line);
  }
  easy_file.close();
}

double ari_function(double ch, double words, double sentences) {
  return (4.71 * (ch / words)) + (0.5 * (words / sentences)) - 21.43;
}

double cli_function(double ch, double words, double sentences) {
  double L = ch / words * 100;
  double S = sentences / words * 100;

  std::cout << L << S;
  return 0.0588 * L - 0.296 * S - 15.8;
}

double fkgl_function(double syllables, double words, double sentences) {
  return 0.39 * (words / sentences) + 11.8 * (syllables / words) - 15.59;
}

double gfi_function(double complex, double words, double sentences) {
  return 0.4 * ((words / sentences) + 100 * (complex / words));
}

double smog_function(double complex, double sentences) {
  return 1.0430 * sqrt(complex * (30 / sentences)) + 3.1291;
}
double dcrs_function(double difficult, double words, double sentences) {
  return 0.1579 * (difficult / words * 100) + 0.0496 * (words / sentences);
}

std::string removeCharsFromFrontAndEnd(const std::string input,
                                       const std::string charsToRemove) {
  size_t start = input.find_first_not_of(charsToRemove);
  size_t end = input.find_last_not_of(charsToRemove);

  if (start == std::string::npos || end == std::string::npos) {
    return "";
  }

  return input.substr(start, end - start + 1);
}
std::string removeCharsFromEnd(const std::string input,
                               const std::string charsToRemove) {
  size_t end = input.find_last_not_of(charsToRemove);

  if (end == std::string::npos) {
    return "";
  }

  return input.substr(0, end + 1);
}

int main(int argc, char *argv[]) {
  std::unordered_map<std::string, int> syllables_map;
  loadSyllables(syllables_map);
  std::unordered_set<std::string> EasySet;
  loadEasySet(EasySet);

  int ch = 0;
  int int_words = 0;
  int sentences = 0;
  int complex_words = 0;
  int difficult_words = 0;

  std::string filter = "abcdefghijklmnopqrstuvwxyz'-";
  std::string sentences_filter = "!?.";
  std::string og_word;
  int total_syll = 0;

  if (argc != 2) {
    std::cerr << "Wrong Arguments" << std::endl;
    return 1;
  }
  while (std::cin >> og_word) {
    // Filtering Words
    std::string filter_sentence = removeCharsFromEnd(og_word, "'\"");

    if (sentences_filter.find(filter_sentence[filter_sentence.size() - 1]) !=
        std::string::npos) {
      ++sentences;
    }

    std::string net;
    for (const auto &letter : og_word) {
      char lowered = std::tolower(letter);
      if (filter.find(lowered) != std::string::npos) {
        net += lowered;
      }
    }
    std::string filter_word = removeCharsFromFrontAndEnd(net, "'-");

    if (filter_word != "") {
      ++int_words;
      auto x = EasySet.find(filter_word);
      if (x == EasySet.end()) {
        ++difficult_words;
      }
    }

    // Counting Syllables and Complex Words and Difficult Words
    auto it = syllables_map.find(filter_word);
    if (it != syllables_map.end()) {
      int word_syll = it->second;
      total_syll += word_syll;
      if (word_syll >= 3) {
        complex_words += 1;
      }
    } else {
      int word_syll = (static_cast<int>(std::ceil((filter_word.size()) / 5.0)));
      total_syll += word_syll;
      if (word_syll >= 3) {
        complex_words += 1;
      }
    }

    ch += size(filter_word);
  }

  // std::cout << "Words:        \t" << int_words << std::endl;
  // std::cout << "sentencess:   \t" << sentences << std::endl;
  // std::cout << "Syllables:    \t" << total_syll << std::endl;
  // std::cout << "Complex Words:\t" << complex_words << std::endl;
  // std::cout << "Diff. Words:  \t" << difficult_words << std::endl;
  // std::cout << "Characters:   \t" << ch << std::endl;

  if ((std::string(argv[1]) == "ari")) {
    std::cout << ari_function(ch, int_words, sentences) << std::endl;
  } else if (std::string(argv[1]) == "cli") {
    std::cout << cli_function(ch, int_words, sentences) << std::endl;
  } else if (std::string(argv[1]) == "fkgl") {
    std::cout << fkgl_function(total_syll, int_words, sentences) << std::endl;
  } else if (std::string(argv[1]) == "gfi") {
    std::cout << gfi_function(complex_words, int_words, sentences) << std::endl;
  } else if (std::string(argv[1]) == "smog") {
    std::cout << smog_function(complex_words, sentences) << std::endl;
  } else if (std::string(argv[1]) == "dcrs") {
    std::cout << dcrs_function(difficult_words, int_words, sentences)
              << std::endl;
  }

  return 0;
}
