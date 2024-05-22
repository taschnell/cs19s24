#ifndef CS19_INTEGER_H
#define CS19_INTEGER_H

/**
 * @file cs19_integer.h
 * @author Teo Schnell for CS 19, teo.schnell@cabrillo.edu
 *
 *
 */

#include <iostream>
#include <string>

namespace cs19 {

class Integer {
 public:
  Integer() : stringValue("0") {}
  friend std::ostream &operator<<(std::ostream &os, const Integer &integer);

  Integer(const char *strValue) : stringValue(strValue) {}
  Integer(const std::string &strValue) : stringValue(strValue) {}

  bool operator==(const Integer &that) const {
    return stringValue == that.stringValue;
  }
  bool operator!=(const Integer &that) const {
    return stringValue != that.stringValue;
  }
  bool operator<(const Integer &that) const {
    if (stringValue.size() != that.stringValue.size()) {
      return stringValue.size() < that.stringValue.size();
    }

    for (size_t i = 0; i < stringValue.size(); ++i) {
      if (stringValue[i] != that.stringValue[i]) {
        return stringValue[i] < that.stringValue[i];
      }
    }

    return false;
  }

  bool operator>(const Integer &that) const { return (that < *this); }
  bool operator<=(const Integer &that) const {
    return (*this < that) || (*this == that);
  }
  bool operator>=(const Integer &that) const {
    return (*this > that) || (*this == that);
  }

  Integer operator+(const Integer &that) const {
    int carry = 0;
    std::string new_str = "";
    int max_length =
        std::max(this->stringValue.size(), that.stringValue.size());

    std::string padded_this =
        std::string(max_length - this->stringValue.size(), '0') +
        this->stringValue;
    std::string padded_that =
        std::string(max_length - that.stringValue.size(), '0') +
        that.stringValue;

    for (int i = max_length - 1; i >= 0; --i) {
      int digit_this = padded_this[i] - '0';
      int digit_that = padded_that[i] - '0';
      int sum = digit_this + digit_that + carry;
      carry = sum / 10;
      new_str = std::to_string(sum % 10) + new_str;
    }

    if (carry > 0) {
      new_str = std::to_string(carry) + new_str;
    }

    return Integer(new_str);
  }
  operator std::string() const { return this->stringValue; }

 private:
  std::string stringValue;
};

std::ostream &operator<<(std::ostream &os, const Integer &integer) {
  os << integer.stringValue;
  return os;
}

}  // namespace cs19

#endif