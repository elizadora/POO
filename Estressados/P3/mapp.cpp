#include <iostream>
#include <vector>

void print(std::vector<int>& fila){
    for (int value : fila){
       std::cout << value << " ";
    }
    std::cout << '\n';
}


std::vector<int> sozinhos(const std::vector<int>& fila){

    std::vector<int> temp {};

    for(int i = 0; i < (int) fila.size(); i++){
        bool unique {true};
        for(int j = 0; j < (int) fila.size(); j++){
            if(i != j && (std::abs(fila[i]) == std::abs(fila[j]))){
                unique = false;

            }
        }
        if(unique) temp.push_back(fila[i]);
    }

    return temp;
}

int mais_ocorrencias(const std::vector<int>& fila){
    int maiorOcorrencia {0};

    for(int i = 0; i < (int) fila.size(); i++){
        int cont {1};
        for(int j = i; j < (int) fila.size(); j++){
            if(i != j && (std::abs(fila[i]) == std::abs(fila[j]))){
                    cont++;
            }
        }
        if(cont > maiorOcorrencia) maiorOcorrencia = cont;
    }

    return maiorOcorrencia;
}

std::vector<int> mais_recorrentes(const std::vector<int>& fila){
    std::vector<int> temp;
    int maior = 0;
    
    for(int i = 0; i < (int) fila.size(); i++){
     int cont = 1;
     for(int j = i+1; j < (int) fila.size(); j++){
       if(abs(fila[i]) == abs(fila[j])){
         cont++;
       }
     }
     
     if(cont > maior) maior = cont;
  } 
  
  for(int i = 0; i < (int) fila.size(); i++){
     int cont = 1;
     for(int j = i+1; j < (int) fila.size(); j++){
       if(abs(fila[i]) == abs(fila[j])){
         cont++;
       }
     }
     
     if(cont == maior) temp.push_back(abs(fila[i]));
  }
  
  return temp;
}



int main(){

    std::vector<int> fila = {1, 3, 4, 5, -1, -5, -5, 3, -3};
    std::vector<int> novaFila {};

    // novaFila = sozinhos(fila);
    // std::cout << mais_ocorrencias(fila);
    
    novaFila = mais_recorrentes(fila);

    print(novaFila);
   

    return 0;
}