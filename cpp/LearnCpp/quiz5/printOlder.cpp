#include <iostream>
#include <string>

using namespace std;

void setOlderYounger(string_view& older_name, int& older_age, string_view& younger_name, int& younger_age) {
    if(older_age < younger_age) {
        string_view temp_name = older_name;
        older_name = younger_name;
        younger_name = temp_name;

        int temp_age = older_age;
        older_age = younger_age;
        younger_age = temp_age;
    }
}

void askName(int num_person, string& name) {
    cout << "Enter the name of person #" << num_person << ": ";
    getline(cin >> std::ws, name);
}

void askAge(string_view name, int& age) {
    cout << "Enter the age of " << name << ": ";
    cin >> age;
}

void askNameAndAge(int num_person, string&name, int& age) {
    askName(num_person, name);
    askAge(name, age);
}

void outputOlderPerson(string_view& person1, int& age1, string_view& person2, int& age2) {
    setOlderYounger(person1, age1, person2, age2);

    cout << person1 << " (age " << age1 << ")" << " is older than " << person2 << " (age " << age2 << ")\n";
}

int main() {
    string person1, person2;
    int age1, age2;
    askNameAndAge(1, person1, age1);
    askNameAndAge(2, person2, age2);

    string_view older = person1;
    string_view younger = person2;
    outputOlderPerson(older, age1, younger, age2);
}