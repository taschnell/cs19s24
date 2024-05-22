#include <iostream>
#include <list>


std::list<int> mylist = {1, 2, 3, 4, 5};

// Forward traversal using iterators
int main(){
    for (auto it = mylist.begin(); it != mylist.end(); ++it) {
        std::cout << *it << " ";
    }
}