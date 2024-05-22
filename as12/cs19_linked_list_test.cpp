/**
 * @file linked_list_smart_pointers_test.cpp
 * @author Jeffrey Bergamini for CS 19, jeffrey.bergamini@cabrillo.edu
 *
 * Let's see if this new LinkedList actually works without memory leaks...
 */
#include "cs19_linked_list_iterable.h"
#include <iostream>
#include <list>
#include <utility>

int main() {
  {
    cs19::LinkedList<std::string> greeting{"A<B<C"};
    cs19::LinkedList<char> test{};

    // std::cout << greeting << '\n';
    std::cout << test.empty() << std::endl;
    std::cout << greeting.size() << std::endl;
    std::cout <<"front" <<greeting.front() << std::endl;
    std::cout << greeting.back() << std::endl;
    std::cout << greeting.pop_front() << std::endl;
    std::cout << greeting << std::endl;

    cs19::LinkedList<char> tester{'H', 'i', '!'};
    std::cout << tester << std::endl;
    tester.reverse();
    std::cout << tester << std::endl;
    tester.resize(10, 'j');
    std::cout << tester << std::endl;

    tester.remove('j');
    tester.push_front('j');

    std::cout << tester << std::endl;

    // We could play with the LinkedList code to see when/how deletion occurs...
  }
  {
    std::list<char> tester{'A', 'B', 'c'};

    std::cout << tester.back() << std::endl;
  }

  cs19::LinkedList<int> int_list;
  for (int i = 0; i < 10; ++i)
    int_list.push_back(i);
  std::cout << int_list << '\n';
  auto other = int_list; // copy constructor
  int_list.push_back(other.pop_back());
  std::cout << int_list << '\n' << other << '\n';

  std::cout << int_list.begin();
}
