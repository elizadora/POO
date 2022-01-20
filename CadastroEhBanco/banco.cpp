#include <iostream>
#include <sstream>
#include <memory>
#include <list>
#include <map>
#include <iomanip>
#include <stdexcept>

class Account{
protected:
    float balance = 0;
    std::string clientId;
    int id;
    std::string type = "";

public:
    Account(int id, std::string clientId){
        this->id = id;
        this->clientId = clientId;
    }

    virtual ~Account(){}
    virtual void monthlyUpdate() = 0;

    friend std::ostream &operator<<(std::ostream& os, const Account& account){
        
        os << account.getId() << ":" << account.getClientId() << ":" << std::setprecision(2) << std::fixed << account.getBalance() << ":" << account.getType();

        return os;
    }

    float getBalance() const{
        return this->balance;
    }

    std::string getClientId() const{
        return this->clientId;
    }

    int getId() const{
        return this->id;
    }

    std::string getType() const{
        return this->type;
    }

    void deposit(float value){
        this->balance += value;
    }

    void transfer(std::shared_ptr<Account> other, float value){
        this->balance -= value;
        other->balance += value;
    }

    void withdraw(float value){
        this->balance -= value;
    }

};

class SavingsAccount : public Account{
public:
    SavingsAccount(int id, std::string clientId) : Account(id, clientId){
       this->type = "CP";
    }
    void monthlyUpdate() override{
        balance += balance * 0.01;
    }

};

class CheckingAccount : public Account{
public:
    CheckingAccount(int id, std::string clientId) : Account(id, clientId) {
       this->type = "CC";
    }

    void monthlyUpdate() override{
        balance -= 20;
    }

};

class Client{
private:
    std::list<std::shared_ptr<Account>> accounts;
    std::string clientId;

public:
    Client(std::string clientId) : clientId{clientId}{
    }

    friend std::ostream &operator<<(std::ostream& os, const Client& client) {
        for(auto& account : client.accounts){
            os << *account << "\n";
        }

        return os;
    }

    std::list<std::shared_ptr<Account>> getAccounts(){
        return this->accounts;
    }

    std::string getClientId(){
        return this->clientId;
    }

    void setAccounts(std::list<std::shared_ptr<Account>> accounts){
        this->accounts = accounts;
    }

    void setClientId(std::string clientId){
        this->clientId = clientId;
    }

    void addAccount(std::shared_ptr<Account> account){
        this->accounts.push_back(account);
    }

};

class BankAgency{
private:
    std::map<int, std::shared_ptr<Account>> accounts;
    std::map<std::string, std::shared_ptr<Client>> clients;
    int nextAccountId = 0;

    std::shared_ptr<Account> getAccount(int id){
        return accounts[id];
    }

public:
    BankAgency() = default;

    friend std::ostream &operator<<(std::ostream& os, const BankAgency& bank){
        
        os << "Clients:\n";

        for(auto& client : bank.clients){
            os << "- " << client.first << "[";
            int i = 1;
            for(auto& clientAccount : client.second.get()->getAccounts()){
                if(i < (int) client.second.get()->getAccounts().size()){
                    os << clientAccount->getId() << ", ";
                    i++;
                }else{
                     os << clientAccount->getId();
                }
            }
            os << "]\n";
        }

        os << "Accounts:\n";

        for(auto& account : bank.accounts){
            os <<  *account.second << "\n";
        }
        
        return os;
    }

    void addClient(std::string clientId){
        this->clients[clientId] = std::make_shared<Client>(clientId);

        this->accounts[nextAccountId] = std::make_shared<CheckingAccount>(nextAccountId, clientId);
        this->clients[clientId].get()->addAccount(this->getAccount(nextAccountId));

        nextAccountId++;
        
        this->accounts[nextAccountId] = std::make_shared<SavingsAccount>(nextAccountId, clientId);
        this->clients[clientId].get()->addAccount(this->getAccount(nextAccountId));

        nextAccountId++;
    }

    void rmClient(std::string clientId){
        auto it = this->clients.find(clientId);
        
        if(it != this->clients.end()){
            this->clients.erase(it);

            for(auto ac = this->accounts.begin(); ac != this->accounts.end(); ac++){
                if(ac->second->getClientId() == clientId){
                    this->accounts.erase(ac);
                }
            }
        }else{
            throw std::invalid_argument("fail: cliente inexistente");
        }

    }

    void deposit(int accountId, float value){
        if(accountId >= nextAccountId || accountId < 0){
            throw std::invalid_argument("fail: conta inexistente");
        }else{
            this->accounts[accountId].get()->deposit(value);
        }
    }

    void monthlyUpdate(){
        for(auto& account : this->accounts){
            account.second->monthlyUpdate();
        }
    }

    void transfer(int accountDe, int accountPara, float value){
       if((accountDe >= nextAccountId) || (accountDe < 0) || (accountPara >= nextAccountId) || (accountPara < 0) ){
           throw std::invalid_argument("fail: conta inexistente");
       }
       else if(this->accounts[accountDe].get()->getBalance() - value < 0 && this->accounts[accountDe].get()->getType() == "CP"){
           throw std::runtime_error("fail: saldo insuficiente");
       }
       else{
            this->accounts[accountDe].get()->transfer(this->accounts[accountPara], value);
       }
    }

    void withdraw(int accountId, float value){
        if((accountId >= nextAccountId) || (accountId < 0)){
            throw std::invalid_argument("fail: conta inexistente");
        }
        else if(this->accounts[accountId].get()->getBalance() - value < 0 && this->accounts[accountId].get()->getType() == "CP"){
            throw std::runtime_error("fail: saldo insuficiente");
        }
        else{
            this->accounts[accountId].get()->withdraw(value);
        }
    }

};

int main(){
    BankAgency bank;

    while(true){
        std::string linha{""};
        std::cout << "$";
        getline(std::cin, linha);

        std::stringstream ss(linha);
        std::string comando;

        ss >> comando;

        try{
           if(comando == "addCli"){
                std::string clientId;

                ss >> clientId;

                bank.addClient(clientId);
            }
            else if(comando == "rmCli"){
                std::string clientId;

                ss >> clientId;

                bank.rmClient(clientId);
            }
            else if(comando == "deposito"){
                int id = -1;
                float value = 0;

                ss >> id >> value;

                bank.deposit(id, value);
            }
            else if(comando == "saque"){
                int id = -1;
                float value = 0;

                ss >> id >> value;

                bank.withdraw(id, value);
            }
            else if(comando == "transf"){
                int idP= -1;
                int idD = -1;
                float value = 0;

                ss >> idD >> idP >> value;

                bank.transfer(idD, idP, value);
            }
            else if(comando == "update"){
                bank.monthlyUpdate();
            }
            else if(comando == "show"){
                std::cout << bank;
            }
            else if(comando == "end"){
                break;
            }
            else{
                std::cout << "Comando invalido\n";
            } 
        }
        catch(const std::exception& e){
            std::cout << e.what() << '\n';
        }
        
    }

    return 0;
}

