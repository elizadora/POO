#include <iostream>
#include <sstream>

struct Pessoa {
    std::string nome;
    int idade;

    Pessoa(std::string nome = "", int idade = 0)
        : nome{nome}, idade{idade}{
    }

    friend std::ostream &operator<<(std::ostream &os, const Pessoa &pessoa) {
        os << "nome: " << pessoa.nome << ", idade:" << pessoa.idade;

        return os;
    }
};

struct Motoca {
    Pessoa *pessoa{nullptr};
    int potencia;
    int tempo;

    Motoca(int potencia = 1): potencia{potencia}, tempo{0}{
    }

    friend std::ostream &operator<<(std::ostream &os, const Motoca &moto) {
        os << "potencia: " << moto.potencia << ", tempo: " << moto.tempo << ", pessoa [";
        
        if (moto.pessoa == nullptr) {
            os << "null";
        }
        else {
            os << *moto.pessoa;
        }

        os << "]\n";

        return os;
    }

    bool inserirPessoa(Pessoa *pessoa) {
        if (this->pessoa != nullptr) {
            std::cout << "Moto cheia\n";
            return false;
        }

        else if (pessoa->idade > 12) {
            std::cout << "Muito grande para andar de moto\n";
            return false;
        }

        this->pessoa = pessoa;
        return true;
    }

    Pessoa *removerPessoa() {
        if(this->pessoa == nullptr){
            std::cout << "Moto vazia\n";
            return nullptr;
        }

        Pessoa *pes = this->pessoa;
        this->pessoa = nullptr;
        return pes;
    }

    bool dirigir(int tempo) {
        if (this->pessoa == nullptr) {
            std::cout << "Nao tem gente na moto\n";
            return false;
        }

        if (tempo > this->tempo) {
            std::cout << "So foi possivel dirigir " << tempo - this->tempo << " min \n";
            this->tempo = 0;
            return true;
        }

        this->tempo -= tempo;
        std::cout << "Resta " << this->tempo << "min\n";
        return true;
    }

    void comprarTempo(int tempo) {
        this->tempo += tempo;
    }

    std::string buzinar() {
        if(this->pessoa == nullptr){
            return "moto vazia\n";
        }

        return "B" + std::string(this->potencia, 'u') + "z\n";
    }
};

void controle(Motoca &moto) {
    std::string linha{""};

    while (true) {

        std::cout << "$";
        getline(std::cin, linha);

        std::stringstream ss(linha);

        std::string comando;

        ss >> comando;

        if (comando == "init") {
            int pot;
            ss >> pot;
            moto.potencia = pot;
        }
        else if (comando == "show") {
            std::cout << moto;
        }
        else if (comando == "in") {
            std::string nome;
            int idade;

            ss >> nome >> idade;

            Pessoa *pessoa = new Pessoa{nome, idade};
            if(!moto.inserirPessoa(pessoa)){
                delete pessoa;
            }
        }
        else if (comando == "out") {
            Pessoa* pessoa = moto.removerPessoa();
            if(pessoa != nullptr){
                delete pessoa;
            }
        }
        else if (comando == "drive") {
            int tempo;
            ss >> tempo;
            moto.dirigir(tempo);
        }
        else if (comando == "buy") {
            int tempo;
            ss >> tempo;
            moto.comprarTempo(tempo);
        }
        else if (comando == "honk") {
            std::cout << moto.buzinar();
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
    Motoca moto;

    controle(moto);

    return 0;
}