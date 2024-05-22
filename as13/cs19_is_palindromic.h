#ifndef CS19_IS_PALINDROMIC_H
#define CS19_IS_PALINDROMIC_H

#include <cmath>

namespace cs19 {

/**
 * Recursively determines whether a given integer is palindromic, i.e. has the
 * same sequence of decimal digits in order from most significant to least, and
 * vice versa. For example:
 *
 * 1
 * 121
 * 12321
 * 1234321
 *
 * @tparam UnsignedInteger any fundamental unsigned integral type
 *
 * @param val the value in question
 * @return whether `val` is palindromic
 */
template <typename UnsignedInteger>
bool is_palindromic(UnsignedInteger val, bool leading_zero = false) {
  if (val < 10) {
    return true;
  }

  // most significant digit
  UnsignedInteger msd = 0;  // Initialize msd
  UnsignedInteger numDigits;
  if (!leading_zero) {
    numDigits = static_cast<UnsignedInteger>(log10(val)) + 1;
    msd = val / static_cast<UnsignedInteger>(pow(10, numDigits - 1));
  } else {
    numDigits = static_cast<UnsignedInteger>(log10(val)) + 2;
  }
  // least significant digit
  UnsignedInteger lsd = val % 10;

  if (msd != lsd) {
    return false;
  }

  // remove the most significant and least significant digits
  UnsignedInteger remainingVal = (val % static_cast<UnsignedInteger>(pow(10, numDigits - 1))) / 10;

  unsigned int second_digit = (val / static_cast<unsigned int>(pow(10, numDigits - 2))) % 10;

  if (second_digit == 0) {
    leading_zero = true;
  } else {
    leading_zero = false;
  }

  return is_palindromic(remainingVal, leading_zero);
}

}  // namespace cs19

#endif  // CS19_IS_PALINDROMIC_H
