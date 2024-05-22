#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "cs19_search_sort.h"

int main() {
  std::vector<int> vec_selection = {64, 25, 12, 22, 11};
  std::vector<int> vec_bubble = {64, 25, 12, 22, 11};

  std::cout << "Original array: ";
  for (int val : vec_selection) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  // Testing selection sort
  auto start = vec_selection.begin();
  auto end = vec_selection.end();
  cs19::selection_sort(start, end);
  std::cout << "Selection Sort Result: ";
  for (int val : vec_selection) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  // Testing bubble sort
  std::cout << "Original array (for Bubble Sort): ";
  for (int val : vec_bubble) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  cs19::bubble_sort(vec_bubble.begin(), vec_bubble.end());
  std::cout << "Bubble Sort Result: ";
  for (int val : vec_bubble) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  int target = 22;
  auto it = cs19::binary_search(vec_bubble.begin(), vec_bubble.end(), target);

  if (it == vec_bubble.end()) {
    std::cout << target << " not found in the array." << std::endl;
  } else {
    std::cout << target << " found at index: " << std::distance(vec_bubble.begin(), it) << std::endl;
  }

  return 0;
}
