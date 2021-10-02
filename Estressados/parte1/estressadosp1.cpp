#include <iostream>
#include <vector>


//Busca

bool existe(std::vector<int> fila, int valorBusca) {
   for (int i = 0; i < (int)fila.size(); i++) {
      if (fila[i] == valorBusca)
         return true;
   }

   return false;
}

int contar(std::vector<int> fila, int valorBusca) {
   int cont = 0;

   for (int i = 0; i < (int)fila.size(); i++) {
      if (fila[i] == valorBusca)
         cont++;
   }

   return cont;
}

int procurar_valor(std::vector<int> fila, int valorBusca) {
   for (int i = 0; i < (int)fila.size(); i++) {
      if (fila[i] == valorBusca)
         return i;
   }

   return -1;
}

int procurar_valor_apos(std::vector<int> fila, int valorBusca, int pos) {
   for (int i = pos; i < (int)fila.size(); i++) {
      if (fila[i] == valorBusca)
         return i;
   }

   return -1;
}

//Melhor caso

int procurar_menor(std::vector<int> fila) {
   int min = 0;

   for (int i = 0; i < (int)fila.size(); i++) {
      if (fila[i] < fila[min])
         min = i;
   }

   return fila[min];
}

int procurar_maior(std::vector <int> fila){
   int max = 0;

   for (int i = 0; i < (int) fila.size(); i++){
      if(fila[i] > fila[max])
         max = i;
   }
   
   return fila[max];
}

int procurar_menor_pos(std::vector<int> fila) {
   int min = 0;

   for (int i = 0; i < (int)fila.size(); i++) {
      if (fila[i] < fila[min])
         min = i;
   }

   return min;
}

int procurar_menor_pos_apartir(std::vector<int> fila, int pos) {
   int menorApos = pos;

   for (int i = pos; i < (int)fila.size(); i++) {
      if (fila[i] < fila[menorApos])
         menorApos = i;
   }

   return menorApos;
}

int procurar_melhor_pos_se(std::vector<int> fila) {
   int posHC = 0;

   for (int i = 0; i < (int)fila.size(); i++) {
      if ((fila[i] > 0) && (fila[i] < fila[posHC]))
         posHC = i;
   }

   if (fila[posHC] > 0)
      return posHC;


   return -1;
}

// Contagem

float calcular_stress_medio(std::vector<int> fila) {
   float media = 0;
   for (int i = 0; i < (int)fila.size(); i++) {
      if (fila[i] < 0)
         media += fila[i] * -1;
      else
         media += fila[i];
   }

   media = media / (int)fila.size();

   return media;
}

std::string mais_homens_ou_mulheres(std::vector<int> fila) {
   int contH = 0;
   int contM = 0;

   for (int i = 0; i < (int)fila.size(); i++) {
      if (fila[i] > 0)
         contH++;
      else
         contM++;
   }

   if (contH == contM)
      return "empate";
   else if (contH > contM)
      return "homens";
   else
      return "mulheres";
}

std::string qual_metade_eh_mais_estressada(std::vector<int> fila) {
   int contPrimeira = 0;
   int contSegunda = 0;

   for (int i = 0; i < (int)fila.size(); i++) {
      if (i < ((int)fila.size() / 2))
         contPrimeira += abs(fila[i]);
      else
         contSegunda += abs(fila[i]);
   }

   if (contPrimeira == contSegunda)
      return "empate";
   else if (contPrimeira > contSegunda)
      return "primeira";
   else
      return "segunda";
}

bool homens_sao_mais_estressados_que_mulheres(std::vector<int> fila) {
   int contH = 0;
   int contM = 0;
   float mediaHomem = 0;
   float mediaMulher = 0;

   for (int i = 0; i < (int)fila.size(); i++) {
      if (fila[i] > 0) {
         contH++;
         mediaHomem += fila[i];
         
      }else {
         contM++;
         mediaMulher += fila[i] * -1;
      }
   }

   mediaMulher = mediaMulher / contM;
   mediaHomem = mediaHomem / contH;

   if (mediaHomem > mediaMulher)
      return true;
   else
      return false;
}

int main() {

   //Busca

   std::cout << existe({-9, - 8, 3, 2, -98, 1}, 1) << "\n"; //true
   std::cout << existe({-9, - 8, 3, 2, -98, 1}, -1) << "\n"; //false

   std::cout << contar({1, 2, -98, 4, 5, 9, 12, 2, -3, 2}, 2) << "\n"; //3
   std::cout << contar({1, 2, -98, 4, 5, 9, 12, 2, -3}, 3) << "\n"; //0

   std::cout << procurar_valor({1, 3, 45, -9, -12, -99, 2, -99}, -99) << "\n"; //5
   std::cout << procurar_valor({1, 3, 45, -9, -12, -99, 2, -99}, -2) << "\n"; //-1

   std::cout << procurar_valor_apos({1, 3, 45, -9, -12, -99, 2, -99}, -99, 6) << "\n"; //7
   std::cout << procurar_valor_apos({1, 3, 45, -9, -12, -99, 2, -99}, -99, 5) << "\n"; //5
   std::cout << procurar_valor_apos({1, 3, 45, -9, -12, -99, 2, -99}, 2, 5) << "\n"; //6


   //Melhor Caso

   std::cout << procurar_menor({1, -55, 12, 99, 87, -2, 7}) << "\n"; //-55

   std::cout << procurar_maior({1, -55, 12, 99, 87, -2, 7}) << "\n"; //99

   std::cout << procurar_menor_pos({1, -55, 12, 99, 87, -2, 7}) << "\n"; //1

   std::cout << procurar_menor_pos_apartir({1, -55, 12, 99, 87, -2, 7}, 3) << "\n"; //5

   std::cout << procurar_melhor_pos_se({5, -55, 12, 99, 87, 2, 7}) << "\n"; //5

   //Contagem 

   std::cout << calcular_stress_medio({5, -55, 10, 14, -20}) << "\n"; //20.8

   std::cout << mais_homens_ou_mulheres({5, -55, 10, 14, -20}) << "\n"; //homens
   std::cout << mais_homens_ou_mulheres({-55, 10, 14, -20}) << "\n"; //empate
   std::cout << mais_homens_ou_mulheres({5, -55, -10, 14, -20}) << "\n"; //mulheres

   std::cout << qual_metade_eh_mais_estressada({60, 3, -4, 9, 12, 33}) << "\n"; //primeira
   std::cout << qual_metade_eh_mais_estressada({66, 1, 2, 99, 5, 2}) << "\n"; //segunda
   std::cout << qual_metade_eh_mais_estressada({60, 2, 3, 5, 59, 1}) << "\n"; //empate

   std::cout << homens_sao_mais_estressados_que_mulheres({-5, -55, 70, 14}) << "\n"; //true
   std::cout << homens_sao_mais_estressados_que_mulheres({-55, 10, 14, -20}) << "\n";  //false

   return 0;
}
