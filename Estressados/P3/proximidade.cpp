#include <iostream>
#include <vector>

void print(std::vector<int>& fila){
    for (int value : fila){
       std::cout << value << " ";
    }
    std::cout << '\n';
}


int briga(const std::vector<int>& fila){
    int cont {0};

    for (int  i = 0; i < (int) fila.size(); i++){
        if((i > 0 && i < (int) fila.size() - 1)  && (abs(fila[i])  > 50 && (abs(fila[i+1]) > 30 &&  abs(fila[i+1]) <= 50)  && (abs(fila[i-1]) > 30 &&  abs(fila[i-1]) <= 50))) cont++;

    }
    
    return cont;

}

std::vector<int> apaziguado(const std::vector<int>& fila){
    std::vector<int> temp {};

    for(int i = 0; i < (int) fila.size(); i++){
        if((i > 0 && i < (int) fila.size() - 1) && (abs(fila[i]) > 80 && (abs(fila[i+1]) < 10 || abs(fila[i-1] < 10)))) temp.push_back(i);
        if(i == 0 && (abs(fila[i]) > 80 && abs(fila[i+1]) < 10)) temp.push_back(i);
        if(i == (int) fila.size() - 1 && (abs(fila[i]) > 80 && abs(fila[i-1]) < 10)) temp.push_back(i);
    }

    if(temp.empty()) temp.push_back(-1);

    return temp;

}

int main(){

    std::vector<int> fila = {83, 90};
    std::vector<int> novaFila {};

    novaFila = apaziguado(fila);

    print(novaFila);

   // std::cout << briga(fila);
   

    return 0;
}