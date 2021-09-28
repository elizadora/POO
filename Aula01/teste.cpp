#include <iostream>

using namespace std;

auto soma(auto a, auto b) {
    return a + b;
}

int main() {
    std::cout << soma(5, 6) << '\n';
    return 0;
}