#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>

class Client{
    private:
        std::string id;
        std::string fone;

    public:
        Client(std::string id = "", std::string fone = "") : id{id}, fone{fone}{}

        friend std::ostream &operator<<(std::ostream &os, const Client &client){
            os << client.id << ":" << client.fone;

            return os;
        }

        std::string getId(){
            return this->id;
        }

        std::string getFone(){
            return this->fone;
        }

        void setId(std::string id){
            this->id = id;
        }

        void setFone(std::string fone){
            this->fone = fone;
        }

};

class Sala{
    private:
        std::map<int, std::shared_ptr<Client>> cadeiras;

        int procurarPessoa(std::string id){
            for(int i = 0; i < (int) cadeiras.size(); i++){
                if(cadeiras[i] != nullptr && cadeiras[i]->getId() == id){
                    return i;
                }
            }

            return -1;
        }

    public:
        Sala(int capacidade = 0){
            for(int i = 0; i < capacidade; i++){
                cadeiras[i] = nullptr;
            }
        }

        int getCadeiras() const{
            return this->cadeiras.size();
        }

        friend std::ostream &operator<<(std::ostream &os, const Sala &sala){
           os << "[ ";

           for(auto cadeira : sala.cadeiras){
               if(cadeira.second == nullptr){
                   os << "- ";
               }else{
                   os << *cadeira.second << " ";
               }
           }

            os << "]\n";

            return os;
        }

        bool reservar(std::string id, std::string fone, int lug){
            if(lug < 0 || lug > this->getCadeiras()){
                std::cout << "Lugar invalido\n";
                return false;
            }

            if(cadeiras[lug] != nullptr){
                std::cout << "Lugar ocupado\n";
                return false;
            }

            if(procurarPessoa(id) != -1){
                std::cout << "Pessoa ja esta no cinema\n";
                return false;
            }

            this->cadeiras[lug] = std::make_shared<Client>(id, fone);
            return true;
        }

        void cancelar(std::string id){
            if(this->cadeiras.empty()){
                std::cout << "Sala vazia\n";
            }else{
                bool result{false};

                if(procurarPessoa(id) != -1){
                    this->cadeiras[procurarPessoa(id)] = nullptr;
                    result = true;
                }

                if(!result) std::cout << "Id invalido\n";
            }
        }     

};


void controle(Sala &sala){
    std::string linha{""};

    while(true){
        std::cout << "$";
        getline(std::cin, linha);

        std::stringstream ss(linha);
        std::string comando;

        ss >> comando;

        if(comando == "init"){
            int capacidade = 0;
            ss >> capacidade;

            Sala salaAux(capacidade);

            sala = salaAux;
        }

        else if(comando == "show"){
            std::cout << sala;
        }

        else if(comando == "reservar"){
            std::string id = ""; 
            std::string fone = "";
            int lugar = -1;

            ss >> id >> fone >> lugar;

            sala.reservar(id, fone, lugar);
        }

        else if(comando == "cancelar"){
            std::string id = "";

            ss >> id;

            sala.cancelar(id);
        }

        else if(comando == "end"){
            break;
        }

        else{
            std::cout << "Comando invalido\n";
        }
    }
}

int main(){
    Sala sala;

    controle(sala);

    return 0;
}