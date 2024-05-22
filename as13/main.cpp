#include <cassert>
#include <cstdint>
#include <set>
#include <iostream>
#include "cs19_is_palindromic.h"
 
int main() {
  // Project Euler Problem 4: Largest palindrome made from the product of two 3-digit numbers
  std::set<int> euler_004_palindromes;
  for (int a = 100; a < 1000; ++a) {
    for (int b = 100; b < 1000; ++b) {
      uint64_t product = a * b;
      if (cs19::is_palindromic(product))
        euler_004_palindromes.insert(product);
    }
  }
  assert(*euler_004_palindromes.rbegin() == 906609);

  std:: cout << cs19::is_palindromic(8048) <<std::endl;
}