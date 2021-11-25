#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

class Fone{
    private:
        std::string id;
        std::string number;
    
    public:
      Fone(std::string id, std::string number) : id{id}, number{number}{}

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

        friend std::ostream &operator<<(std::ostream& os, Contact& contact){
            os << contact.prefix << " " << contact.name;

            if(!contact.fones.empty()){
                for(int i = 0; i < (int) contact.fones.size(); i++){
                    os << " [" << i << ":" << contact.fones[i] << "]";
                }
            }

            return os;
        }

        std::string getName(){
            return this->name;
        }

        std::vector<Fone> getFones(){
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


class Agenda{
    private:
        std::vector<Contact> contacts;

        int findPos(std::string name){
            for(int i = 0; i < (int) this->contacts.size(); i++){
                if(name == contacts[i].getName()){
                    return i;
                }
            }

            return -1;
        }

        void ordernar(){
            std::sort(this->contacts.begin(), this->contacts.end(), [](Contact contact1, Contact contact2){
                return contact1.getName() < contact2.getName();
            });
        }
    
    public:
        Agenda(){

        }

        friend std::ostream& operator<<(std::ostream& os, Agenda agenda){
            for(auto contato : agenda.contacts){
                os << contato << '\n';
            }

            return os;
        }

        void breakFone(std::stringstream& ss, Contact* contact){
            std::string temp;

            while(ss >> temp){
               std::string id{""};
               std::string number{""};

               int pos = temp.find(":");

               id = temp.substr(0, pos);
               number = temp.substr(pos + 1);

               Fone fone(id, number);

               contact->addFone(fone);
           }
        }

        void addContact(Contact contact){
            this->contacts.push_back(contact);
            ordernar();
        }

        Contact* getContact(std::string name){
            int pos = findPos(name);

            if(pos != -1){
                return &this->contacts[pos];
            }

            return nullptr;
        }

        void rmContact(std::string name){
            int pos = findPos(name);

            if(pos != -1){
                this->contacts.erase(this->contacts.begin() + pos);

            }else{
                std::cout << "Contato invalido\n";
            }
        }

        std::vector<Contact> search(std::string pattern){
            std::vector<Contact> result;

            for(auto& contact : this->contacts){
                std::stringstream ss;
                ss << contact;

                std::string text = ss.str();

                if(text.find(pattern) != std::string::npos){
                    result.push_back(contact);
                }
            }

            return result;
        }

        std::vector<Contact> getContacts(){
            return this->contacts;
        }
};


void controle(Agenda& agenda){
    std::string linha{""};

    while(true){
        std::cout << "$";

        getline(std::cin, linha);

        std::stringstream ss(linha);
        std::string comando;

        ss >> comando;

        if(comando == "init"){
           agenda = Agenda();
        }

        else if(comando == "show"){
            std::cout << agenda;
        }

        else if(comando == "add"){
           std::string name;

           ss >> name;
        
           if(agenda.getContact(name) == nullptr){
                Contact contact;
                contact.setName(name);
                agenda.breakFone(ss, &contact);
                agenda.addContact(contact);

           }else{
               agenda.breakFone(ss, agenda.getContact(name));
           }
        }

        else if(comando == "rm"){
           std::string name;

           ss >> name;

           agenda.rmContact(name);
        }

        else if(comando == "rmFone"){
            std::string name;
            int id;

            ss >> name >> id;
            agenda.getContact(name)->rmFone(id);

            if(agenda.getContact(name)->getFones().size() == 0){
                agenda.rmContact(name);
            }
        }

        else if(comando == "end"){
            break;
        }

        else if(comando == "search"){
            std::string pattern;

            ss >> pattern;

            std::vector<Contact> result = agenda.search(pattern);

            if((int) result.size() == 0){
                std::cout << "Nada foi encontrado\n";

            }else{
                for(auto contact : result){
                    std::cout << contact << "\n";
                }
            }

        }
        
        else{
            std::cout << "Comando invalido\n";
        }
    }
}


int main(){
    Agenda agenda;

    controle(agenda);

    return 0;
}
