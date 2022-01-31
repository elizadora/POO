#include <iostream>
#include <vector>

//Função para printar vetor

void print(std::vector<int>& fila){
    for (int value : fila){
       std::cout << value << " ";
    }
    std::cout << '\n';
}

//Map - Manipulação

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
    int maior {0};
    
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


//Proximidade

int briga(const std::vector<int>& fila){
    int cont {0};

    for (int  i = 0; i < (int) fila.size(); i++){
        if((i > 0 && i < (int) fila.size() - 1)  && (abs(fila[i])  > 50 && abs(fila[i+1]) > 30 && abs(fila[i-1]) > 30)) cont++;

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


// Sequências

int quantos_times(const std::vector<int>& fila){
    
    int times {0};
    int contPositivo {0};
    int contNegativo {0};

    for(int i = 0; i < (int) fila.size(); i++){  
        
        if(fila[i] > 0){
          contPositivo++;
          
          if(fila[i+1] < 0 && i+1 < (int) fila.size()){
            if(contPositivo > 1){
                  times++;
              contPositivo = 0;
            } 
          }
          contNegativo = 0;
        }else{
          contNegativo++;
          
          if(fila[i+1] > 0 && i+1 < (int) fila.size()){
            if(contNegativo > 1){
              times++;
              contNegativo = 0;
            } 
          }
          contPositivo = 0;
        } 
    }
    return times;
}

int maior_time(std::vector<int>& fila){
   int contPositivo {0};
   int contNegativo {0};
   int maiorTime {0};

    for(int i = 0; i < (int) fila.size(); i++){  
        
        if(fila[i] > 0){
          contPositivo++;
          
          if(fila[i+1] < 0 && i+1 < (int) fila.size()){
            if(contPositivo > 1){
              if(maiorTime < contPositivo) maiorTime = contPositivo;
              contPositivo = 0;
            } 
          }
          contNegativo = 0;
        }else{
          contNegativo++;
          
          if(fila[i+1] > 0 && i+1 < (int) fila.size()){
            if(contNegativo > 1){
              if(maiorTime < contNegativo) maiorTime = contNegativo;
              contNegativo = 0;
            } 
          }
          contPositivo = 0;
        } 
    }
    
    return maiorTime;
}

int sozinhos_time(std::vector<int>& fila){
  
  int sozinhos {0};
  
  for(int i = 0; i < (int) fila.size(); i++){
    if(((i > 0 && i < (int) fila.size() - 1) && fila[i] > 0 && fila[i-1] < 0 && fila[i+1] < 0) ||(i == 0 && fila[i] > 0 && fila[i+1] < 0) ||(i == (int) fila.size() - 1 && fila[i] > 0 && fila[i-1] < 0)) 
        sozinhos++;
    
    if(((i > 0 && i < (int) fila.size() - 1) && fila[i] < 0 && fila[i-1] > 0 && fila[i+1] > 0) ||(i == 0 && fila[i] < 0 && fila[i+1] > 0) ||(i == (int) fila.size() - 1 && fila[i] < 0 && fila[i-1] > 0))
        sozinhos++;
  
  }
    
    return sozinhos;
}


// Grupos

int casais(const std::vector<int>& fila){
  std::vector<int> temp{fila};
  int contCasais {0};
  
  for(int i = 0; i < (int) temp.size(); i++){
    for(int j = i; j < (int) temp.size(); j++){
      if(i != j && temp[i] == (temp[j] * -1)){
        contCasais++;
        temp.erase(temp.begin() + i);
        temp.erase(temp.begin() + j-1);
        i = -1;
        break;
      }
    }
  }
  return contCasais;
}

int trios(const std::vector<int>& fila){
  std::vector<int> temp{fila};
  std::vector<int> posFila {};
  
  int trios {0};
  
  for(int i = 0; i < (int) temp.size(); i++){
    int cont{0};
    for(int j = 0; j < (int) temp.size(); j++){
      if(abs(temp[i]) == abs(temp[j])){
        cont++;
        posFila.push_back(j);
         if(cont == 3){
           trios++;
           for(int h = 2; h >= 0; h--){
            temp.erase(temp.begin() + posFila[h]);
           }
           break;
         }
      }
    }
    posFila.clear();
  }  
  return trios;
}


//Alteração

std::vector<int> remove(const std::vector<int>& fila, int pos){
   std::vector<int> temp {fila};
   
   temp.erase(temp.begin() + pos);
   
   return temp; 
}

std::vector<int> insert(const std::vector<int>& fila, int value, int pos){
   std::vector<int> temp {fila};
   
   temp.insert(temp.begin() + pos, value);
   
   return temp; 
}

std::vector<int> dance(const std::vector<int>& fila){
  std::vector<int> temp {fila};
  
  for(int i = 0; i < (int) temp.size() -1; i++){
    if(abs(temp[i]) == abs(temp[i+1])){
      temp.erase(temp.begin() + i);
      temp.erase(temp.begin() + i);
      i = -1;
    }
  }
  
  return temp;
}



int main(){


    //Map - Manipulação

    std::vector<int> fila = {1, 3, 4, 5, -1, -5, -5, 3, -3};
    std::vector<int> novaFila {};

    novaFila = sozinhos(fila);
    print(novaFila);
    
    std::cout << mais_ocorrencias(fila) << '\n';
    
    novaFila = mais_recorrentes(fila);
    print(novaFila);
   

    //Proximidade

    fila = {50, 98, 31, -51, 31, -90, 89, -7};

    std::cout << briga(fila) << '\n';

    novaFila = apaziguado(fila);
    print(novaFila);


    //Sequências

    fila =  {5, 3, 1, 3, -11, 1, 9, -11, -1, -2, 44, -66};

    std::cout << quantos_times(fila) << '\n';

    std::cout << maior_time(fila) << '\n';

    std::cout << sozinhos_time(fila);


    //Grupos
    
    fila =  {3, -3, 3, -3, 4, 9, 8, 10, -10, -9, 90, 62, 9};
    
    std::cout << casais(fila) << '\n';

    std::cout << trios(fila) << '\n';


    //Alteração

    fila = {3, 3, 5, 6, -6, 5, -89, 12, -70, -12, 12};

    novaFila = remove(fila, 2);
    print(novaFila);

    novaFila = insert(fila, -78, 1);
    print(novaFila);

    novaFila = dance(fila);
    print(novaFila);

    return 0;
}