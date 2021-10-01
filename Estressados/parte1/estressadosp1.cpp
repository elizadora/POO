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

int procurar_menor_pos_apos(std::vector<int> fila, int pos) {
   int menorApos = pos;

   for (int i = pos; i < (int)fila.size(); i++) {
      if (fila[i] < fila[menorApos])
         menorApos = i;
   }

   return menorApos;
}

int procurar_melhor_se(std::vector<int> fila) {
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
      if (fila[i] < 0) {
         media += fila[i] * -1;
      }else{
         media += fila[i];
      }
   }

   media = media / (int)fila.size();

   return media;
}

std::string mais_homens_ou_mulheres(std::vector<int> fila) {
   int contH = 0;
   int contM = 0;

   for (int i = 0; i < (int)fila.size(); i++) {
      if (fila[i] > 0){
         contH++;
      }else {
         contM++;
      }
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
      if (i < ((int)fila.size() / 2)) {
         contPrimeira += abs(fila[i]);
      }else {
         contSegunda += abs(fila[i]);
      }
   }

   if (contPrimeira == contSegunda)
      return "empate";
   else if (contPrimeira > contSegunda)
      return "primeira";
   else
      return "segunda";
}

std::string homens_sao_mais_estressados_que_mulheres(std::vector<int> fila)
{
   int contH = 0;
   int contM = 0;
   float mediaHomem = 0;
   float mediaMulher = 0;

   for (int i = 0; i < (int)fila.size(); i++)
   {
      if (fila[i] > 0)
      {
         contH++;
         mediaHomem += fila[i];
      }
      else
      {
         contM++;
         mediaMulher += fila[i] * -1;
      }
   }

   mediaMulher = mediaMulher / contM;
   mediaHomem = mediaHomem / contH;

   if (mediaHomem == mediaMulher)
      return "a media de stress deu empate";
   else if (mediaMulher > mediaHomem)
      return "a media de stress das mulheres";
   else
      return "a media de stress dos homens";
}

int main() {
   

   return 0;
}