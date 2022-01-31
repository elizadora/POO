#include <iostream>
#include <ctime>
#include <sstream>

class Animal{

private:
    bool alive;

protected:
    std::string nickname;

public:
    Animal() : alive{true}{
        this->nickname = "Animal";
    }

     friend std::ostream &operator<<(std::ostream& os, const Animal& animal){
        os << "estado: " << (animal.alive ? "vivo" : "morto") << '\n';

        return os;
     }

    bool isAlive(){
        return this->alive;
    }

    virtual void dead(){
        this->alive = false;
    }

    virtual void eat(){
        std::cout << this->nickname << " esta comendo\n";
    }

};


class Mammal : public Animal{

private:
    std::string order;
    std::string habitat;

public:
    
    Mammal(std::string order, std::string habitat) : order{order}, habitat{habitat}{

    }

    friend std::ostream &operator<<(std::ostream& os, const Mammal& mammal){
        const Animal& animal = mammal;

        os << "classe: mamifero\n" << "ordem: " << mammal.order << '\n' << "habitat: " << mammal.habitat << '\n';
        os << animal;

        return os;
     }

    virtual void dead(){
        if(isAlive()){
            Animal::dead();
            std::cout << this->nickname << " morreu\n";
        }else{
            std::cout << this->nickname << " ja esta morto\n";
        }
    }

    void move(){
        std::cout << this->nickname << " esta em movimento\n";
    }

    void sleep(){
        std::cout << this->nickname << " esta em dormindo\n";
    }

};


class Wolf : public Mammal{

private:
    std::string species;
    
public:
    Wolf(std::string nick = "", std::string species = "", std::string habitat = "") : Mammal{"carnivoro", habitat}, species{species} {
        this->nickname = nick;
    }

    friend std::ostream &operator<<(std::ostream& os, const Wolf& wolf){
        const Mammal& mammal = wolf;

       
        os << "apelido: " << wolf.nickname << "\nespecie: " << wolf.species << "\n" << mammal;

        return os;
     }

    void hunt(){
        std::srand(std::time(0));

        int res = rand() % 2;

        std::cout << this->nickname << " esta caçando\n";

        if(res == 1){
            Animal::eat();
        }else{
            std::cout << this->nickname << " nao conseguiu capturar a presa\n";
        }
    }

};

void controle() {

    Wolf wolf;

    std::string linha{""};

   while(true){
        std::cout << "$";
        getline(std::cin, linha);

        std::stringstream ss(linha);

        std::string comando;

        ss >> comando;

        if (comando == "init") {
            std::string nick;
            std::string species;
            std::string habitat;

            ss >> nick >> species >> habitat;

            wolf = Wolf(nick, species, habitat);
        }
        else if (comando == "show") {
            std::cout << wolf;
        }
        else if (comando == "hunt") {
            wolf.hunt();
        }
        else if (comando == "dead") {
            wolf.dead();
        }
        else if (comando == "end") {
            break;
        }
        else{
            std::cout << "Comando nao existe\n";
        }
   }
}


int main(){
    controle();

    return 0;
}