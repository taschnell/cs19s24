#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#include "cs19_linked_list_iterable.h"

template <typename Container>
void time_removal(Container *container, const std::string &description) {
  auto start = std::chrono::high_resolution_clock::now();
  for (auto it = container->begin(); it != container->end();) {
    if (it->back() == 's')
      it = container->erase(it);
    else
      ++it;
  }
  auto finish = std::chrono::high_resolution_clock::now();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
  std::cout << "Removing all strings ending in 's' while iterating a " << description << " took "
            << milliseconds.count() << " ms" << std::endl;
}

int main(int argc, char **argv) {
  std::ifstream in_file(argv[1]);
  std::vector<std::string> word_vector((std::istream_iterator<std::string>(in_file)),
                                       std::istream_iterator<std::string>());
  std::list<std::string> word_list(word_vector.begin(), word_vector.end());
  cs19::LinkedList<std::string> our_list(word_vector.begin(), word_vector.end());
  time_removal(&word_list, "std::list<std::string>");
  time_removal(&our_list, "cs19::LinkedList<std::string>");
  time_removal(&word_vector, "std::vector<std::string>");
  assert(word_list.size() == word_vector.size() && word_vector.size() == our_list.size());
  assert(std::equal(our_list.begin(), our_list.end(), word_list.begin()));
}