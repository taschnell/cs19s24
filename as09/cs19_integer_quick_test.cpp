/**
 * @file cs19_integer_quick_test.cpp
 *
 * Uses the C++ bindings for the GNU Multiprecision Library to test cs19::Integer.
 *
 * We need to tell GCC to include the GMP library during linking:
 * g++ cs19_integer_quick_test.cpp cs19_integer.cpp -lgmp
 */

#include <gmpxx.h>
#include <cassert>
#include <iostream>
#include <string>
#include "cs19_integer.h"

int main() {
  // Construction and comparison tests:
  cs19::Integer four("19");
  cs19::Integer eight("00990");
  assert(four < eight);
  assert(four <= eight);
  assert(eight > four);
  assert(eight >= four);
  assert(four == cs19::Integer("19"));
  assert(four != eight);
  assert(four + eight == cs19::Integer("1009"));
  // Addition and string-conversion tests:
  mpz_class control_sum;   // GNU MP class-style integer
  cs19::Integer test_sum;  // cs19::Integer object
  for (std::string input; std::cin >> input;) {
    control_sum = control_sum + mpz_class(input);  // add to the GMP integer
    test_sum = test_sum + cs19::Integer(input);    // add to the CS 19 integer
    std::cout << "C: " << control_sum.get_str() << "\nT: " << test_sum << '\n';
    assert(control_sum.get_str() == std::string(test_sum));  // string representations should match
  }
 }