#include <iostream>
#include <sstream>
#include <vector>

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

        std::string getId() const{
            return this->id;
        }

        std::string getFone() const{
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
        std::vector<Client> cadeiras;

    public:
        Sala(int capacidade = 0){
            if(capacidade > 0){
                for(int i = 0; i < capacidade; i++){
                    Client cli;
                    this->cadeiras.push_back(cli);
                }
            }
        }

        int getCadeiras() const{
            return this->cadeiras.size();
        }

        friend std::ostream &operator<<(std::ostream &os, const Sala &sala){
            if(sala.cadeiras.empty()){
                os << "[ ]\n";
            }else{
                os << "[ ";

                for(int i = 0; i < sala.getCadeiras(); i++){
                    if(sala.cadeiras[i].getId() == ""){
                        os << "- ";
                    }else{
                        os << sala.cadeiras[i] << " ";
                    }
                }

                os << "]\n";                

            }

            return os;
        }

        bool reservar(std::string id, std::string fone, int lug){
            if(lug < 0 || lug > this->getCadeiras() || this->getCadeiras() == 0){
                std::cout << "Lugar invalido\n";
                return false;
            }

            if(this->cadeiras[lug].getId() != ""){
                std::cout << "Lugar ocupado\n";
                return false;
            }

            for(int i = 0; i < this->getCadeiras(); i++){
                if(this->cadeiras[i].getId() == id){
                    std::cout << "Pessoa ja esta presente na sala\n";
                    return false;
                }
            }

            Client cli(id, fone);
            this->cadeiras[lug] = cli;
            return true;
        }

        void cancelar(std::string id){
            if(this->cadeiras.empty()){
                std::cout << "Sala vazia\n";
            }else{
                bool result{false};

                for(int i = 0; i < this->getCadeiras(); i++){
                    if(this->cadeiras[i].getId() == id){
                        Client cli;
                        this->cadeiras[i] = cli;
                        result = true;
                    }
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