#include <iostream>
#include "cs19_is_palindromic.h"

int main() {
    // Test cases
    unsigned int palindromicNumbers[] = {1, 121, 12321, 1234321};
    unsigned int nonPalindromicNumbers[] = {123, 1234, 12345};

    // Test palindromic numbers
    std::cout << "Testing palindromic numbers:\n";
    for (unsigned int num : palindromicNumbers) {
        std::cout << num << " is ";
        if (!cs19::is_palindromic(num)) {
            std::cout << "not ";
        }
        std::cout << "palindromic.\n";
    }

    // Test non-palindromic numbers
    std::cout << "\nTesting non-palindromic numbers:\n";
    for (unsigned int num : nonPalindromicNumbers) {
        std::cout << num << " is ";
        if (cs19::is_palindromic(num)) {
            std::cout << "not ";
        }
        std::cout << "palindromic.\n";
    }

    return 0;
}
