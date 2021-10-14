#include <iostream>
#include <vector>

void print(std::vector<int>& fila){
    for (int value : fila){
       std::cout << value << " ";
    }
    std::cout << '\n';
}


int quantos_times(const std::vector<int>& fila){
    int cont {0};

    for(int i = 0; i < (int) fila.size(); i++){
        if(fila[i] < 0){
            while(fila[i+1] < 0){
                
            }
        }
    }

    return cont;
}


int main(){

    std::vector<int> fila = {5, 3, 1, -11, 1, 99, -11, -1, -2, 44}


    return 0;
}