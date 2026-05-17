#include <iostream>

using namespace std;

void printOutput(double x, double y, char op, double res) {
    cout << x << " " << op << " " << y << " is " << res << "\n";
}

int main() {
    double x,y;
    char op;
    cout << "Enter in a number" << "\n";
    cin >> x;
    cout << "Enter another number" << "\n";
    cin >> y;
    cout << "Enter one of the characters +, -, *, /" << "\n";
    cin >> op;

    switch(op) {
        case '*':
        printOutput(x, y, op, x*y);
        break;

        case '/':
        printOutput(x, y, op, x/y);
        break;

        case '+':
        printOutput(x, y, op, x+y);
        break;

        case '-':
        printOutput(x, y, op, x-y);
        break;

        default:
        break;
    }
}