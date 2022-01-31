#include <iostream>
#include <list>
#include <memory>
#include <sstream>

class Kid {
    private:
        int age;
        std::string name;

    public:
        Kid(std::string name = "", int age = 0) : age{age}, name{name}{}

        friend std::ostream &operator<<(std::ostream& os, Kid &kid){
            os << kid.name << ":" << kid.age;

            return os;
        }

        int getAge(){
            return this->age;
        }

        std::string getName(){
            return this->name;
        }

        void setAge(int age){
            this->age = age;
        }

        void setName(std::string name){
            this->name = name;
        }
};

class Trampoline{

    private:
        std::list <std::shared_ptr<Kid>> playing;
        std::list <std::shared_ptr<Kid>> waiting;

        Kid remove_kid(std::string name, std::list<std::shared_ptr<Kid>>& kids){
            Kid kid(name);
            Kid kidFail;
            
            if(kids.empty()){
                std::cout << "Fila vazia\n";
                return kidFail;
            }else{
                bool find = false;
                
                for(auto it = kids.begin(); it != kids.end(); it++){
                    if(it->get()->getName() == kid.getName()){
                        kids.erase(it);
                        find = true;
                    }
                }

                if(find) return kid;

                return kidFail;
            }
        }

    public:
        Trampoline(){

        }

        friend std::ostream &operator<<(std::ostream& os, const Trampoline &trampoline){
            os << "=> ";
            if(!trampoline.waiting.empty()){
                for(auto it = trampoline.waiting.rbegin();  it != trampoline.waiting.rend(); it++){
                    os << *it->get() << " ";
                }
            }
            
             os << "=> [ ";

             if(!trampoline.playing.empty()){
                for(auto jt = trampoline.playing.rbegin();  jt != trampoline.playing.rend(); jt++){
                     os << *jt->get() << " ";
                }
            }

            os << "]\n";

            return os;
        }

        void arrive(const std::shared_ptr<Kid>& kid){
            this->waiting.push_back(kid);
        }

        void in(){
            if(this->waiting.empty()){
                std::cout << "Fila de espera vazia\n";
            }else{
                this->playing.push_back(this->waiting.front());
                this->waiting.pop_front();
            }
        }

        void out(){
            if(this->playing.empty()){
                std::cout << "Trampolim vazio\n";
            }else{
                this->waiting.push_back(this->playing.front());
                this->playing.pop_front();
            }
        }

        Kid remove(std::string name){
            return this->remove_kid(name, this->waiting);
        }


};


void controle(Trampoline &trampoline){
    std::string linha{""};

    while(true){
        std::cout << "$";
        getline(std::cin, linha);

        std::stringstream ss(linha);
        std::string comando;

        ss >> comando;

        if(comando == "arrive"){
            std::string name = "";
            int age = 0;

            ss >> name >> age;

            trampoline.arrive(std::make_shared<Kid>(name, age));
        }

        else if(comando == "show"){
            std::cout << trampoline;
        }

        else if(comando == "in"){
            trampoline.in();
        }

        else if(comando == "out"){
            trampoline.out();
        }
        
        else if(comando == "remove"){
            std::string name;

            ss >> name;

            Kid kid = trampoline.remove(name);

            if(kid.getName() != "") std::cout << kid.getName() << " foi embora\n";
            else std::cout << "Não foi possivel remover a crianca\n";
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
    Trampoline trampoline;

    controle(trampoline);

    return 0;
}