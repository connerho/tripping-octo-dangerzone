#include <iostream>


int main() {
    int first_int;
    int second_int;
    std::cout << "Enter an integer: ";
    std::cin >> first_int;
    std::cout << "Enter another integer: ";
    std::cin >> second_int;

    std::cout << first_int << " + " << second_int << " is " << (first_int+second_int) << "\n";
    std::cout << first_int << " - " << second_int << " is " << (first_int-second_int) << "\n";

    return 0;
}