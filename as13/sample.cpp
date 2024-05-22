#include <iostream>
#include <cmath>

int main() {
    unsigned int num = 136662345; // Example unsigned integer

    // Find the number of digits in the integer
    int num_digits = static_cast<int>(log10(num)) + 1;

    // Extract the second digit from the front
    unsigned int second_digit = (num / static_cast<unsigned int>(pow(10, num_digits - 2))) % 10;

    // Print the second digit from the front
    std::cout << "Second digit from the front: " << second_digit << std::endl;

    return 0;
}
