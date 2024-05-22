/**
 * @file search_sort_quick_tests.cpp
 *
 * This file runs some tests on the function templates in our search and sort
 * assignment for CS 19.
 *
 * @author A student in CS 19, somestudent@jeff.cis.cabrillo.edu
 */

#include "cs19_search_sort.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <forward_list>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <vector>

template <typename Integer> struct AuditedInteger {
  Integer n_;
  static inline int _total_comparisons = 0;

  AuditedInteger() = default;
  AuditedInteger(Integer n) : n_(n) {}

  auto operator<=>(const AuditedInteger &that) const {
    ++_total_comparisons;
    return this->n_ <=> that.n_;
  }

  operator int() const { return this->n_; }

  operator char() const { return this->n_; }
};

// Repeatedly uses `cs19::insertion_position()` to compute the position at which
// to insert a value, then inserts the value and verifies the sortedness
// invariant and logarithmic comparison counts.
template <typename IntegerSequence, typename Integer>
void test_binary_search(std::mt19937 &prng, const size_t container_size,
                        Integer min_value, Integer max_value) {
  std::uniform_int_distribution<Integer> random_element(min_value, max_value);
  IntegerSequence data;
  for (int i = 0; i < 1000; ++i) {
    auto num = AuditedInteger<Integer>{random_element(prng)};
    AuditedInteger<Integer>::_total_comparisons = 0;
    auto new_pos = cs19::insertion_position(data.begin(), data.end(), num);
    // Computing the insertion position for `num` should require at most
    // ~log2(n) comparisons:
    assert(data.empty() || AuditedInteger<Integer>::_total_comparisons <=
                               std::ceil(std::log2(data.size()) + 1));
    data.insert(new_pos, num); // num should now be inserted in order (likely
                               // not fast/efficient!)
    AuditedInteger<Integer>::_total_comparisons = 0;
    // A binary search should now find the value, and use at most ~log2(n)
    // comparisons:
    assert(*cs19::binary_search(data.begin(), data.end(), num) == num);
    assert(AuditedInteger<Integer>::_total_comparisons <=
           std::ceil(std::log2(data.size()) + 1));
    // The data should still be sorted due to using our specific insertion
    // point:
    assert(std::is_sorted(data.begin(), data.end()));
  }
}

// Fills a container with random values, calls a function to sort it, and
// verifies its sortedness.
template <typename IntegerSequence, typename Integer, typename SortingFunction>
void test_sort(std::mt19937 &prng, const size_t container_size,
               Integer min_value, Integer max_value, SortingFunction function) {
  std::uniform_int_distribution<Integer> random_element(min_value, max_value);
  std::vector<Integer> vector_data;
  for (int i = 0; i < 1000; ++i)
    vector_data.push_back(random_element(prng));
  IntegerSequence data(vector_data.begin(), vector_data.end());

  AuditedInteger<Integer>::_total_comparisons = 0;
  function(data.begin(), data.end()); // call the sorting function
  // Worst-case general-purpose sorts should never do more than n^2 comparisons
  assert(AuditedInteger<Integer>::_total_comparisons <=
         std::pow(vector_data.size(), 2));
  // for (auto i = data.begin(); i != data.end(); ++i) {
  //   std::cout << *i << " ";
  // }
  // std::cout << std::endl;
  assert(std::is_sorted(data.begin(), data.end()));
}

// Test the binary-search-related and sorting-related functions using some
// randomly generated data.
int main() {
  std::random_device random_device;
  std::mt19937 prng(random_device());
  test_binary_search<std::vector<AuditedInteger<int>>>(prng, 1000, 0, 10);
  test_binary_search<std::basic_string<AuditedInteger<char>>>(prng, 1000, 'A',
                                                              'z');
  test_sort<std::vector<AuditedInteger<int>>>(
      prng, 1000, 0, 10,
      cs19::bubble_sort<std::vector<AuditedInteger<int>>::iterator>);
  test_sort<std::list<AuditedInteger<char>>>(
      prng, 1000, 'A', 'z',
      cs19::bubble_sort<std::list<AuditedInteger<char>>::iterator>);
  test_sort<std::forward_list<AuditedInteger<char>>>(
      prng, 1000, 'A', 'z',
      cs19::bubble_sort<std::forward_list<AuditedInteger<char>>::iterator>);
  test_sort<std::string>(prng, 1000, 'A', 'z',
                         cs19::bubble_sort<std::string::iterator>);
  test_sort<std::vector<AuditedInteger<int>>>(
      prng, 1000, 0, 10,
      cs19::selection_sort<std::vector<AuditedInteger<int>>::iterator>);
  test_sort<std::list<AuditedInteger<char>>>(
      prng, 1000, 'A', 'z',
      cs19::selection_sort<std::list<AuditedInteger<char>>::iterator>);
  test_sort<std::basic_string<AuditedInteger<char>>>(
      prng, 1000, 'A', 'z',
      cs19::selection_sort<std::basic_string<AuditedInteger<char>>::iterator>);
  test_sort<std::forward_list<AuditedInteger<char>>>(
      prng, 1000, 'A', 'z',
      cs19::selection_sort<std::forward_list<AuditedInteger<char>>::iterator>);
}
