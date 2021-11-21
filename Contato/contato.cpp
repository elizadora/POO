#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class Fone{
    private:
        std::string id;
        std::string number;
    
    public:
        Fone(std::string id, std::string number) : id{id}, number{number} {};

        friend std::ostream &operator<<(std::ostream& os, const Fone& fone){
            
            os << fone.getId() << ":" << fone.getNumber();

            return os;

        }

        static bool validade(std::string number){
            for(int i = 0; i < (int) number.length(); i++){
                if((number[i] < 48  && number[i] != 40 && number[i] != 41 && number[i] != 46) || number[i] > 57){
                    return false;
                }
            }

            return true;
        }

        std::string getId() const{
            return this->id;
        }

        std::string getNumber() const{
            return this->number;
        }

        void setId(std::string id){
            this->id = id;
        }

        void setNumber(std::string number){
            this->number = number;
        }

};


class Contact{
    private:
        std::string name;
        std::vector<Fone> fones;

    protected:
        std::string prefix = "-";

    public:
        Contact(){

        }

        Contact(std::string name, std::vector<Fone> fones) : name{name}, fones{fones} {}

        friend std::ostream &operator<<(std::ostream& os, const Contact& contact){
            os << contact.prefix << " " << contact.name;

            if(!contact.fones.empty()){
                for(int i = 0; i < (int) contact.fones.size(); i++){
                    os << " [" << i << ":" << contact.fones[i] << "]";
                }
            }

            os << "\n";

            return os;
        }

        std::string getName() const{
            return this->name;
        }

        std::vector<Fone> getFones() const{
            return this->fones;
        }
        
        void setName(std::string name){
            this->name = name;
        }

        void addFone(Fone fone){
            if(Fone::validade(fone.getNumber())){
                this->fones.push_back(fone);
            }else{
                std::cout << "Numero invalido\n";
            }
        }

        void rmFone(int id){
            if(this->fones.empty()){
                std::cout << "Sem telefones para remover\n";

            }else if(id < 0 || id > (int) this->fones.size() - 1){
                std::cout << "Id invalido\n";

            }else{
                this->fones.erase(this->fones.begin() + id);
            }
        }


};

void controle(Contact& contact){
    std::string linha{""};

    while(true){
        std::cout << "$";

        getline(std::cin, linha);

        std::stringstream ss(linha);
        std::string comando;

        ss >> comando;

        if(comando == "init"){
            std::string name;
            std::string id;
            std::string number;
            std::vector<Fone> fones;

            ss >> name;

            while(ss >> id >> number){
                Fone fone(id, number);
                fones.push_back(fone);
            }

            Contact contAux(name, fones);

            contact = contAux;

        }

        else if(comando == "show"){
            std::cout << contact;
        }

        else if(comando == "add"){
            std::string id;
            std::string number;

            ss >> id >> number;

            contact.addFone(Fone(id, number));

        }

        else if(comando == "rm"){
            int index{-1};

            ss >> index;

            contact.rmFone(index);
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
    Contact contact;

    controle(contact);

    return 0;
}