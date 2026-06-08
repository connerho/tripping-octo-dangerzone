#include <iostream>
#include <string>
#include <string_view>

using std::string;
using std::string_view;

class Fruit {
private:
    string name {};
    string color {};

public:
    Fruit (string_view myName, string_view myColor) : name{myName}, color{myColor} {}

    const string& getName() const { return name; }
    const string& getColor() const { return color; }
};

class Banana : public Fruit {
public:
    Banana (string_view name, string_view color) : Fruit{name, color} {}
};

class Apple : public Fruit {
private:
    double fiber {};

public:
    Apple (string_view name, string_view color, double myFiber) : Fruit{name, color}, fiber{myFiber}{}

    double getFiber() const { return fiber; }
};

std::ostream& operator<<(std::ostream& out, const Apple& apple) {
    out << "Apple(" << apple.getName() << ", " << apple.getColor() << ", " << apple.getFiber() << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Banana& banana) {
    out << "Banana(" << banana.getName() << ", " << banana.getColor() << ")";
    return out;
}

int main() {
    const Apple a{ "Red delicious", "red", 4.2 };
    std::cout << a << '\n';

    const Banana b{ "Cavendish", "yellow" };
    std::cout << b << '\n';

    return 0;
}