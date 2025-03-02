#include <iostream>

// It is possible to use the namespace std instead of typing "std::" everywhere

int main() {
    std::cout << "Bytes used by the int: " << sizeof(int) << "\n";
    std::cout << "Hi, what's your name?\n";

    std::pmr::string name = "";
    std::cin >> name;

    std::cout << "Hello " << name << "!\n";

    return 0; // Return nothing
}