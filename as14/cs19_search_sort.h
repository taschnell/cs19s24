/**
 * @file cs19_search_sort.h
 *
 * This file contains some function templates for our search and sort assignment
 * in CS 19.
 *
 * @author A student in CS 19, somestudent@jeff.cis.cabrillo.edu
 */

#ifndef CS19_SEARCH_SORT_H_
#define CS19_SEARCH_SORT_H_

namespace cs19 {

/**
 * Performs a binary search for `val` in `[first, last)`, assuming the values in
 * `[first, last)` are already sorted in ascending order.
 *
 * @tparam RandomIt must meet the requirements of `LegacyRandomAccessIterator`
 * @tparam Value a type both convertible and comparable to the elements in range
 * `[first, last)`
 * @see https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
 *
 * @param first the beginning of the range of elements to examine
 * @param last past the end of the range of elements to examine
 * @return an iterator in `[first, last)` pointing to `val`, or `last` if `val`
 * was not found
 */
template <typename RandomIt, typename Value>
RandomIt binary_search(RandomIt first, RandomIt last, Value val) {
  if (first == last) {
    return last;
  }
  auto temp_first = first;
  auto temp_last = last - 1;
  while (temp_first <= temp_last) {
    auto middle = temp_first + (temp_last - temp_first) / 2;
    if (*middle == val) {
      return middle;
    } else if (*middle > val) {
      if (middle == first) {
        return last;
      }
      temp_last = middle - 1;
    } else {
      temp_first = middle + 1;
    }
  }
  return last;
}

/**
 * Uses a binary search to locate the insertion position for `val` in `[first,
 * last)` to maintain sorted order, assuming the values in `[first, last)` are
 * already sorted in ascending order. If `val` is already present, the insertion
 * position will be before (to the left of) any existing entries. The return
 * value is suitable for use as the first argument to any of the various
 * `container::insert(iterator, value)` functions in the STL containers.
 *
 * @tparam RandomIt must meet the requirements of `LegacyRandomAccessIterator`
 * @tparam Value a type both convertible and comparable to the elements in range
 * `[first, last)`
 * @see https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
 *
 * @param first the beginning of the range of elements to examine
 * @param last past the end of the range of elements to examine
 */
template <typename RandomIt, typename Value>
RandomIt insertion_position(RandomIt first, RandomIt last, Value val) {
  auto temp_first = first;
  auto temp_last = last;
  while (temp_first < temp_last) {
    auto middle = temp_first + (temp_last - temp_first) / 2;
    if (*middle < val) {
      temp_first = middle + 1;
    } else {
      temp_last = middle;
    }
  }
  return temp_first;
}

/**
 * Sorts the elements in the range `[first,last)` in ascending order, using the
 * bubble-sort algorithm. The elements are compared using `operator<`.
 *
 * @tparam InputIt must meet the requirements of `LegacyInputIterator`
 *
 * @param first the initial position in the sequence to be sorted
 * @param last one element past the final position in the sequence to be sorted
 * @see https://en.cppreference.com/w/cpp/named_req/InputIterator
 */
template <typename InputIt> void bubble_sort(InputIt first, InputIt last) {
  if (first == last)
    return;

  bool swapped = true;
  for (InputIt it = first; it != last; ++it) {
    swapped = false;
    for (InputIt jt = first; jt != last; ++jt) {
      InputIt next = jt;
      ++next;
      if (next != last && *jt > *next) {
        auto temp = *jt;
        *jt = *next;
        *next = temp;
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
  }
}

/**
 * Sorts the elements in the range `[first,last)` into ascending order,
 * using the selection-sort algorithm.
 *
 * @tparam InputIt must meet the requirements of `LegacyInputIterator`
 *
 * @param first the initial position in the sequence to be sorted
 * @param last one element past the final position in the sequence to be sorted
 * @see https://en.cppreference.com/w/cpp/named_req/InputIterator
 */

template <typename InputIt> void selection_sort(InputIt first, InputIt last) {
  if (first == last)
    return;

  for (InputIt it = first; it != (last); ++it) {
    InputIt min_it = it;
    for (InputIt jt = next(it); jt != (last); ++jt) {
      if ((next(it)) == (last))  // check for last element
        break;
      // auto i = *jt;
      // auto j = *it;
      if (*jt < *min_it) {
        min_it = jt;
      }
    }
    if (min_it != it) {
      auto temp = *it;
      *it = *min_it;
      *min_it = temp;
    }
  }
}

}  // namespace cs19

#endif  // CS19_SEARCH_SORT_H_
