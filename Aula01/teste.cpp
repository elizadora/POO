#include <iostream>

auto soma(auto a, auto b) {
    return a + b;
}
auto subtracao(auto a, auto b){
	return a - b;
}
int main() {
    int num1 = 0, num2 = 0;
    std::cin >> num1 >> num2;
    
    std::cout << "Soma: "<< soma(num1, num2) << '\n';
    std::cout << "Subtracao: "<< subtracao(num1, num2) << '\n';
    std::cout << __cplusplus << std::endl;

    return 0;
}
