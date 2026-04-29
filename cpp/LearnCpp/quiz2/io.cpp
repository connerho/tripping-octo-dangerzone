#include <iostream>
#include "io.h"

int readNumber() {
    int user;
    std::cout << "Enter a number: ";
    std::cin >> user;

    return user;
}

void writeAnswer(int answer) {
    std::cout << "The answer is:\t" << answer << "\n";
}