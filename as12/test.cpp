/**
 * @file cs19_linked_list_iterable_test.cpp
 *
 * Testing the iterator-based functions in cs19::LinkedList.
 *
 * @author Jeffrey Bergamini for CS 19, jbergamini@jeff.cis.cabrillo.edu
 */
#include "cs19_linked_list_iterable.h"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <list>

template <typename T>
void compare_lists(std::list<T>& stl_list, cs19::LinkedList<T>& our_list) {
  std::copy(stl_list.begin(), stl_list.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;
  std::copy(our_list.begin(), our_list.end(), std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;
  assert(stl_list.size() == our_list.size());
  auto stl_iterator = stl_list.begin();
  auto our_iterator = our_list.begin();
  while (our_iterator != our_list.end() && stl_iterator != stl_list.end()) {
    assert(*our_iterator++ == *stl_iterator++);
  }
  assert(our_iterator == our_list.end() && stl_iterator == stl_list.end());
}

int main() {
  std::list<int> stl_list{1, 2, 3, 4, 5};
  cs19::LinkedList<int> our_list{1, 2, 3, 4, 5};

  auto stl_iterator = stl_list.begin();
  auto our_iterator = our_list.begin();
  while (our_iterator != our_list.end() && stl_iterator != stl_list.end()) {
    our_list.insert(our_iterator, 10);
    stl_list.insert(stl_iterator, 10);
    compare_lists(stl_list, our_list);
    ++our_iterator;
    ++stl_iterator;
  }

  stl_list.insert(stl_iterator, std::size_t(5), 99);
  our_list.insert(our_iterator, std::size_t(5), 99);
  compare_lists(stl_list, our_list);

  assert(stl_iterator == stl_list.end());
  assert(our_iterator == our_list.end());

  stl_list.insert(stl_iterator, {2, 4, 6, 0, 1});
  our_list.insert(our_iterator, {2, 4, 6, 0, 1});
  compare_lists(stl_list, our_list);

  stl_iterator = stl_list.begin();
  our_iterator = our_list.begin();
  stl_list.erase(stl_iterator);
  our_list.erase(our_iterator);
  compare_lists(stl_list, our_list);

  stl_iterator = stl_list.begin();
  our_iterator = our_list.begin();
  std::advance(stl_iterator, stl_list.size() / 2);
  std::advance(our_iterator, our_list.size() / 2);
  stl_list.erase(stl_iterator);
  our_list.erase(our_iterator);
  compare_lists(stl_list, our_list);

  stl_iterator = stl_list.end();
  --stl_iterator;
  our_iterator = our_list.end();
  --our_iterator;
  stl_list.erase(stl_iterator);
  our_list.erase(our_iterator);
  compare_lists(stl_list, our_list);

  auto stl_start_erase = stl_list.begin();
  auto our_start_erase = our_list.begin();
  std::advance(stl_start_erase, 9);
  std::advance(our_start_erase, 9);
  auto stl_end_erase = stl_start_erase;
  auto our_end_erase = our_start_erase;
  std::advance(stl_end_erase, 4);
  std::advance(our_end_erase, 4);
  stl_list.erase(stl_start_erase, stl_end_erase);
  our_list.erase(our_start_erase, our_end_erase);
  compare_lists(stl_list, our_list);

  std::list<int> stl_donation{100, 200, 300};
  cs19::LinkedList<int> our_donation{100, 200, 300};
  stl_iterator = stl_list.begin();
  our_iterator = our_list.begin();
  std::advance(stl_iterator, stl_list.size() / 2);
  std::advance(our_iterator, our_list.size() / 2);
  stl_list.splice(stl_iterator, stl_donation);
  our_list.splice(our_iterator, our_donation);
  compare_lists(stl_list, our_list);
  assert(stl_donation.size() == our_donation.size());

  stl_donation = {500, 600, 700};
  our_donation = {500, 600, 700};
  stl_iterator = stl_list.begin();
  our_iterator = our_list.begin();
  std::advance(stl_iterator, stl_list.size() / 2);
  std::advance(our_iterator, our_list.size() / 2);
  stl_list.splice(stl_iterator, stl_donation, stl_donation.begin());
  our_list.splice(our_iterator, our_donation, our_donation.begin());
  compare_lists(stl_list, our_list);
  assert(stl_donation.size() == our_donation.size());

  stl_donation = {1000, 2000, 3000, 4000, 5000, 6000, 7000};
  our_donation = {1000, 2000, 3000, 4000, 5000, 6000, 7000};
  auto stl_donation_start = stl_donation.begin();
  auto our_donation_start = our_donation.begin();
  std::advance(stl_donation_start, 2);
  std::advance(our_donation_start, 2);
  auto stl_donation_stop = stl_donation_start;
  auto our_donation_stop = our_donation_start;
  std::advance(stl_donation_stop, 3);
  std::advance(our_donation_stop, 3);
  stl_list.splice(stl_iterator, stl_donation, stl_donation_start, stl_donation_stop);
  our_list.splice(our_iterator, our_donation, our_donation_start, our_donation_stop);
  compare_lists(stl_list, our_list);
  assert(stl_donation.size() == our_donation.size());
}