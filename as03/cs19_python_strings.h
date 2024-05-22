/**
 * @file python_strings.h
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 *
 * Interface for some string- and dynamic-allocation-related functions.
 * Examples of expected return values are given in header comments.
 *
 * For the purposes of counting/matching, an empty string is considered to be
 * at the beginning of any string, at the end of any string, and between each
 * character in any string.
 */

#ifndef CS19_PYTHON_STRINGS_H_
#define CS19_PYTHON_STRINGS_H_

#include <stddef.h>  // for size_t

/**
 * Returns the number of occurrences of a given character in a string.
 *
 * cs19_str_count_char("banana", 'a') == 3
 * cs19_str_count_char("banana", 'x') == 0
 *
 * @param str the string to search
 * @param val the value to count
 * @return the number of occurrences of `val` in `str`
 */
size_t cs19_str_count_char(const char *str, char val);

/**
 * Returns the number of non-overlapping occurrences a substring within a string.
 *
 * cs19_str_count_str("apple", "pp") == 1
 * cs19_str_count_str("aaaaa", "aa") == 2
 * cs19_str_count_str("apple", "banana") == 0
 * cs19_str_count_str("fig", "") == 4
 *
 * @param str the string to search
 * @param substr the substring to find
 * @return the number of occurrences of `substr` in `str`
 */
size_t cs19_str_count_str(const char *str, const char *substr);

/**
 * Returns the lowest index in a string where a given character is found.
 *
 * cs19_str_find_char("apple", 'p') == 1
 * cs19_str_find_char("banana", 'x') == -1
 *
 * @param str the string to search
 * @param val the value to find
 * @return the lowest index in `str` where `val` is found, or `-1` if `val` is not found
 */
int cs19_str_find_char(const char *str, char val);

/**
 * Returns the lowest index in a string where a given substring is found.
 *
 * cs19_str_find_str("apple", "pp") == 1
 * cs19_str_find_str("aaaaa", "aa") == 0
 * cs19_str_find_str("apple", "banana") == -1
 * cs19_str_find_str("fig", "") == 0
 *
 * @param str the string to search
 * @param substr the substring to find
 * @return the lowest index in `str` where `subtr` is found, or `-1` if `val` is not found
 */
int cs19_str_find_str(const char *str, const char *substr);

/**
 * Returns a newly heap-allocated string which is the concatenation of the characters in another
 * string, with a separator string inserted between each character.
 *
 * strcmp(cs19_str_join("apple", "/"), "a/p/p/l/e") == 0
 * strcmp(cs19_str_join("fig", "__"), "f__i__g") == 0
 * strcmp(cs19_str_join("", "banana"), "") == 0
 *
 * @param str a string to start with
 * @param sep the separator string to be placed between each character from `str` in the output
 * @return a newly heap-allocated string containing the concatenation of each character in `str`,
 *         with the entirety of `sep` between each character. It is the caller's responsibility to
 *         free this string.
 */
char *cs19_str_join(const char *str, const char *sep);

/**
 * Returns a newly heap-allocated string which contains the contents of a given string with certain
 * leading and trailing characters removed.
 *
 * strcmp(cs19_str_strip("   spacious   ", " "), "spacious") == 0
 * strcmp(cs19_str_strip("www.example.com", "cmowz."), "example") == 0
 *
 * @param str a string to start with
 * @param chars a set of values to strip from either end of `str`
 * @return a newly heap-allocated copy of `str` with all values in `chars` removed from both ends.
 *         It is the caller's responsibility to free this string.
 */
char *cs19_str_strip(const char *str, const char *chars);

/**
 * Returns a newly heap-allocated string which contains the contents of a given string with certain
 * characters translated to other characters.
 *
 * strcmp(cs19_str_translate("happiness", "aeiou", "xxxxx"), "hxppxnxss") == 0
 * strcmp(cs19_str_translate("apple", "aple", "lmon"), "lmmon") == 0
 *
 * @param str a string to start with
 * @param from a string of characters to replace
 * @param to a string of characters (of the same length as `from`) with which to replace the
 *           characters in `from`
 * @return a newly heap-allocated copy of `str` with all values in `from` replaced with the
 *         characters in `to` at the same index. It is the caller's responsibility to
 *         free this string.
 */
char *cs19_str_translate(const char *str, const char *from, const char *to);

#endif