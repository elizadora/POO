#include <iostream>
#include <sstream>

struct Grafite {

    float calibre;
    std::string dureza;
    int tamanho;

    Grafite(float calibre = 0, std::string dureza = "", int tamanho = 0) : calibre{calibre}, dureza{dureza}, tamanho{tamanho}{
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Grafite &lapiseira) {

        os << "Grafite: [" << lapiseira.calibre << ":" << lapiseira.dureza << ":" << lapiseira.tamanho << "]\n";

        return os;
    }
    
    int desgastePorFolha() {
        if (this->dureza == "HB") {
            return 1;
        }else if (this->dureza == "2B") {
            return 2;
        }else if (this->dureza == "4B") {
            return 4;
        }else if (this->dureza == "6B") {
            return 6;
        }else {
            return 0;
        }
    }
};

struct Lapiseira {

    float calibre;
    Grafite *grafite;

    Lapiseira(float calibre = 0, Grafite *grafite = nullptr) : calibre{calibre}, grafite{grafite} {
    }

    friend std::ostream &operator<<(std::ostream &os, const Lapiseira &lapiseira) {
        os << "Calibre: " << lapiseira.calibre << ", ";

        if (nullptr == lapiseira.grafite) {
            os << "Grafite: null\n";
        }else {
            os << *lapiseira.grafite;
        }

        return os;
    }


    void orint() {
        std::cout << this->grafite->calibre;
    }

    bool inserirGrafite(Grafite *grafite) {

        if (this->grafite != nullptr) {
            std::cout << "Uma grafite ja foi inserida\n";
            return false;
        }

        if (this->calibre != grafite->calibre) {
            std::cout << "O calibre da grafite é incompatível com o da lapiseira\n";
            return false;
        }

        this->grafite = grafite;

        return true;
    }

    Grafite *removerGrafite() {
        if (this->grafite == nullptr) {
            std::cout << "A lapiseira nao tem grafite\n";
        }

        Grafite *temp = this->grafite;
        this->grafite = nullptr;
        return temp;
    }

    void escreverFolhas(int folhas) {
        int temp = 0;

        if (this->grafite == nullptr) {
            std::cout << "A grafite ainda nao foi inserida para poder escrever\n";
        }
        else {
            while (this->grafite->tamanho > 0 && folhas > 0) {
                if (this->grafite->tamanho - this->grafite->desgastePorFolha() < 0){
                    break;
                }

                this->grafite->tamanho -= this->grafite->desgastePorFolha();
                folhas--;
                temp++;
            }

            if (this->grafite->tamanho == 0) {
                std::cout << "A grafite acabou\n";
                delete this->grafite;
                this->grafite = nullptr;
            }
            if (folhas > 0){
                std::cout << "Foram escritas: " << temp << " folhas";
            }
               
        }
    }
};

bool controle(Lapiseira &lapiseira) {

    std::string linha{""};

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
    if (comando == "show") {
        std::cout << lapiseira;
    }
    if (comando == "insert") {

        float calibre;
        std::string dureza;
        int tamanho;

        ss >> calibre >> dureza >> tamanho;

        Grafite *grafite = new Grafite{calibre, dureza, tamanho};
        lapiseira.inserirGrafite(grafite);

        return true;
    }
    if (comando == "remove") {
        lapiseira.removerGrafite();
    }
    if (comando == "write") {
        int folhas;
        ss >> folhas;
        lapiseira.escreverFolhas(folhas);
    }
    if (comando == "end") {
        return false;
    }

    return true;
}

int main() {
    Lapiseira lapiseira;

    while (controle(lapiseira));

    return 0;
}