#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

//Print vector

void print(std::vector<int>& fila){
    for (int value : fila){
       std::cout << value << " ";
    }
    std::cout << '\n';
}

// Filtro

std::vector<int> clone(const std::vector<int>& fila){
  
   std::vector<int> filaClone {fila};
 
   return filaClone; 
}

std::vector<int> pegar_homens(const std::vector<int>& fila){
  
  std::vector<int> listaHomens {};
  
  for(int value : fila){
    if(value > 0) listaHomens.push_back(value);
  }
  
  return listaHomens;
  
}

std::vector<int> pegar_calmos(const std::vector<int>& fila){
  
  std::vector<int> calmos {};
  
  for(int value : fila){
    if(std::abs(value) < 10) calmos.push_back(value);
  }
  
  return calmos;
}

std::vector<int> pegar_mulheres_calmas(const std::vector<int>& fila){
  
  std::vector<int> mulheresCalmas {};
  
  for(int value : fila){
    if(value < 0 && value > -10) mulheresCalmas.push_back(value);
  }
  
  return mulheresCalmas;
  
}



//Acesso

std::vector<int> inverter_com_copia(const std::vector<int>& fila){
  std::vector<int> filaInversa {fila};
  
  for(int i = 0; i < ((int) filaInversa.size())/2; i++){
    std::swap(filaInversa[i], filaInversa[(int) filaInversa.size() - 1 - i]);
  }
  
  return filaInversa;
}

void inverter_inplace(std::vector<int>& fila){
  
  for(int i = 0; i < ((int) fila.size())/2; i++){
    std::swap(fila[i], fila[(int) fila.size() - 1 - i]);
  }
  
}

int sortear(const std::vector<int>& fila){
  std::srand(std::time(0));

  int pos = rand() % (int)fila.size();
  
  return fila[pos];
  
}

void embaralhar(std::vector<int>& fila){
  std::srand(std::time(0));

  for(int i = 0; i < (int) fila.size(); i++){
    int pos = rand() % (int)fila.size();
     std::swap(fila[pos], fila[i]);
  }
  
}

void ordenar(std::vector<int>& fila){
  std::sort(fila.begin(), fila.end());
}


//Conjuntos

std::vector<int> exclusivos(const std::vector<int>& fila){
  std::vector<int> exclu = fila;
  
  for(int i = 0; i < (int) exclu.size(); i++){
    for(int h = 0; h < (int) exclu.size(); h++){
      if(i != h && exclu[i] == exclu[h]){
           exclu.erase(exclu.begin() + h);
      }
    }
  }
  
  return exclu;
  
}

std::vector<int> diferentes(const std::vector<int>& fila){
  std::vector<int> exclu = fila;
  
  for(int i = 0; i < (int) exclu.size(); i++){
    for(int h = 0; h < (int) exclu.size(); h++){
      if(h != i && abs(exclu[i]) == abs(exclu[h])){
          exclu.erase(exclu.begin() + h);
      }
    }
  }
  
  return exclu;
}

std::vector<int> abandonados(const std::vector<int>& fila){
  
  std::vector<int> exclu{};
  
  for(int i = 0; i < (int) fila.size(); i++){
    for(int h = i; h < (int) fila.size(); h++){
      if((h != i) && fila[i] == fila[h]){
          exclu.push_back(fila[h]);
          break;
       }
    }
  }
  
  return exclu;
}



int main(){
  
  std::vector<int> fila = {-60, -7, -1, 3, 6, 9, -80, 19, 6, 3, 12};
  std::vector<int> novaFila = {};
  
  //Filtro 

  novaFila = clone(fila);
  print(novaFila);

  novaFila = pegar_homens(fila);
  print(novaFila);

  novaFila = pegar_calmos(fila);
  print(novaFila);
  
  novaFila = pegar_mulheres_calmas(fila);
  print(novaFila);
  

  //Acesso 

  novaFila = inverter_com_copia(fila);
  print(novaFila);

  inverter_inplace(fila);
  print(fila);

  std::cout << sortear(fila) << '\n';

  embaralhar(fila);
  print(fila);

  ordenar(fila);
  print(fila);


  //Conjuntos

  novaFila = exclusivos(fila);
  print(novaFila);

  novaFila = diferentes(fila);
  print(novaFila);

  novaFila = abandonados(fila);
  print(novaFila);

  
 return 0;
}
