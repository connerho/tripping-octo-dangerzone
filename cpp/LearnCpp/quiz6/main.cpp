#include <iostream>
#include <string>

std::string_view getQuantityPhrase(int param) {
    if(param < 0) {
        return "negative";
    } else if (param == 0) {
        return "no";
    } else if (param == 1) {
        return "a single";
    } else if (param == 2) {
        return "a couple of";
    } else if (param == 3) {
        return "a few";
    } else {
        return "many";
    }
}

std::string_view getApplesPluralized(int param) {
    return (param == 1) ? "apple" : "apples";
}

int main()
{
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";

    return 0;
}