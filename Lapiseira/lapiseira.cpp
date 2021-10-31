#include <iostream>
#include <sstream>
#include <vector>

struct Grafite {

    float calibre;
    std::string dureza;
    int tamanho;

    Grafite(float calibre = 0, std::string dureza = "", int tamanho = 0) : calibre{calibre}, dureza{dureza}, tamanho{tamanho} {
    }

    friend std::ostream &operator<<(std::ostream &os, const Grafite &lapiseira) {

        os << "Grafite: [" << lapiseira.calibre << ":" << lapiseira.dureza << ":" << lapiseira.tamanho << "]\n";

        return os;
    }

    int desgastePorFolha() {

        if (this->dureza == "HB") {
            return 1;
        }
        else if (this->dureza == "2B") {
            return 2;
        }
        else if (this->dureza == "4B") {
            return 4;
        }
        else if (this->dureza == "6B") {
            return 6;
        }
        else {
            return 0;
        }
    }
};

struct Lapiseira {

    float calibre;
    std::vector<Grafite> grafites;

    Lapiseira(float calibre = 0) : calibre{calibre} {
    }

    friend std::ostream &operator<<(std::ostream &os, const Lapiseira &lapiseira) {
        
        os << "Calibre: " << lapiseira.calibre << "\n";
        if(lapiseira.grafites.empty()){
            os << "Grafite: null\n";
        }else{
            for (int i = 0; i < (int)lapiseira.grafites.size(); i++) {
                os << lapiseira.grafites[i];
            }   

        }
        return os;
    }

    bool inserirGrafite(Grafite &grafite) {

        if (grafite.calibre != this->calibre) {
            std::cout << "Calibre incorreto\n";
            return true;
        }
        if ((int)this->grafites.size() == 4) {
            std::cout << "Quantidade maxima de grafites foi atingida\n";
            return true;
        }
        this->grafites.push_back(grafite);

        return true;
    }

    std::vector<Grafite> removerGrafite(int i) {

        if (this->grafites.empty()) {
            std::cout << "Nenhuma grafite foi inserida\n";
            return this->grafites;
        }
        std::vector<Grafite> temp = this->grafites;
        this->grafites.erase(this->grafites.begin() + i);

        return temp;
    }

    void escreverFolhas(int folhas) {
        int temp = 0;

        if (this->grafites.empty()) {
            std::cout << "A grafite ainda nao foi inserida para poder escrever\n";

        }else {

            for (int i = 0; i < (int)this->grafites.size(); i++) {
                while (this->grafites[i].tamanho > 0 && folhas > 0) {
                    this->grafites[i].tamanho -= this->grafites[i].desgastePorFolha();

                    if (this->grafites[i].tamanho >= 0) {
                        folhas--;
                        temp++;
                    }
                    if (this->grafites[i].tamanho <= 0) {
                        this->grafites.erase(this->grafites.begin() + i);
                    }
                }
            }
            if (folhas > 0 && this->grafites.empty()) {
                std::cout << "As grafites acabaram\n";
                std::cout << "Foram escritas apenas: " << temp << " folhas\n";
            }
        }
    }
};

void controle(Lapiseira &lapiseira) {

    std::string linha{""};

   while(true){
        std::cout << "$";
        getline(std::cin, linha);

        std::stringstream ss(linha);

        std::string comando;

        ss >> comando;

        if (comando == "init") {
            float calibre;
            ss >> calibre;
            lapiseira.calibre = calibre;
        }
        else if (comando == "show") {
            std::cout << lapiseira;
        }
        else if (comando == "insert") {

            float calibre;
            std::string dureza;
            int tamanho;

            ss >> calibre >> dureza >> tamanho;

            Grafite grafite{calibre, dureza, tamanho};
            lapiseira.inserirGrafite(grafite);

        }
        else if (comando == "remove") {
            int i;
            ss >> i;

            lapiseira.removerGrafite(i);
        }
        else if (comando == "write") {
            int folhas;

            ss >> folhas;

            lapiseira.escreverFolhas(folhas);
        }
        else if (comando == "end") {
            break;
        }
        else{
            std::cout << "Comando nao existe\n";
        }
   }
}

int main() {
    Lapiseira lapiseira;

   controle(lapiseira);

    return 0;
}