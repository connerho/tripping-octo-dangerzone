#include "io.h"

int main(){

    int user_input_1 = readNumber();
    int user_input_2 = readNumber();
    writeAnswer(user_input_1 + user_input_2);

    return 0;
}