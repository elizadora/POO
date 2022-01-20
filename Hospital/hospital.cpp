#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <algorithm>

class MessageException : public std::exception {
   std::string message;
public:
    MessageException(const std::string& message) : 
        message(message) {
    }
    const char* what() const noexcept override {
        return message.c_str(); 
    }
};

class IMedico;

class IPaciente{
public:
    virtual void addMedico(IMedico* medico) = 0;
    virtual std::string getDiagnostico() = 0;
    virtual std::string getId() = 0;
    virtual std::vector<IMedico*> getMedicos() = 0;
    virtual void removerMedico(std::string medicoId) = 0;
    virtual std::string toString() = 0;
    virtual ~IPaciente(){};
};

class IMedico{
public:
    virtual void addPaciente(IPaciente* paciente) = 0;
    virtual std::string getClasse() = 0;
    virtual std::string getId() = 0;
    virtual std::vector<IPaciente*> getPacientes() = 0;
    virtual void removerPaciente(std::string pacienteId) = 0;
    virtual std::string toString() = 0;
    virtual ~IMedico(){};
};

class Paciente : public IPaciente{
protected:
    std::string id;
    std::string diagnostico;
    std::map<std::string, IMedico*> medicos;

public:
    Paciente(std::string id, std::string diagnostico) : id{id}, diagnostico{diagnostico} {}
    
    std::string toString() override{
        std::stringstream ss;
        int size = 1;

        ss << "Pac: " << this->getId() << ":" << this->getDiagnostico() << "  Meds[";
        
        for(auto medico : this->getMedicos()){
            if(size < (int) this->getMedicos().size()){
                ss << medico->getId() << ",";
            }else{
                ss << medico->getId();
            }

            size++;    
        }

        ss << "]";
        
        return ss.str();
    }

    void addMedico(IMedico* medico) override{
        this->medicos[medico->getId()] = medico;
    }

    std::string getDiagnostico() override{
        return this->diagnostico;
    }

    std::string getId() override{
        return this->id;
    }

    std::vector<IMedico*> getMedicos() override{
        std::vector<IMedico*> temp;

        for(auto medico : this->medicos){
            temp.push_back(medico.second);
        }

        return temp;
    }

    void removerMedico(std::string medicoId) override{
        this->medicos.erase(medicoId);
    }
};

class Medico : public IMedico{
protected:
    std::string id;
    std::string classe;
    std::map<std::string, IPaciente*> pacientes;

public:
    Medico(std::string id, std::string classe) : id{id}, classe{classe} {}

    std::string toString() override{
        std::stringstream ss;
        int size = 1;

        ss << "Med: " << this->getId() << ":" << this->getClasse()<< "  Pacs[";

        for(auto paciente : this->getPacientes()){
            if(size < (int) this->getPacientes().size()){
                ss << paciente->getId() << ",";
            }else{
                ss << paciente->getId();
            }

            size++;    
        }

        ss << "]";

        return ss.str();
    }

    void addPaciente(IPaciente* paciente) override{
        this->pacientes[paciente->getId()] = paciente;
    };

    std::string getClasse() override{
        return this->classe;
    }

    std::string getId() override{
        return this->id;
    }

    std::vector<IPaciente*> getPacientes() override{
        std::vector<IPaciente*> temp;

        for(auto paciente : this->pacientes){
            temp.push_back(paciente.second);
        }

        return temp;
    }

    void removerPaciente(std::string pacienteId) override{
        this->pacientes.erase(pacienteId);
    }
};

class Hospital{
private:
    std::map<std::string, std::shared_ptr<IPaciente>> pacientes;
    std::map<std::string, std::shared_ptr<IMedico>> medicos;

public:
    Hospital(){}

    void addMedico(std::shared_ptr<IMedico> medico){
       if(this->medicos.find(medico->getId()) == this->medicos.end()){
            medicos[medico->getId()] = medico;
       }else{
           throw MessageException("fail: medico ja cadastrado");
       }
    }

    void addPaciente(std::shared_ptr<IPaciente> paciente){
        if(this->pacientes.find(paciente->getId()) == this->pacientes.end()){
            pacientes[paciente->getId()] = paciente;
        }else{
            throw MessageException("fail: paciente ja cadastrado");
        }
    }

    void removerMedico(std::string id) {
        if(this->medicos.find(id) != this->medicos.end()){
            for(auto paciente : this->medicos[id].get()->getPacientes()){
                paciente->removerMedico(id);
            }
            this->medicos.erase(id);
        }else{
            throw MessageException("fail: medico nao encontrado");
        }
    }

    void removerPaciente(std::string id) {
        if(this->pacientes.find(id) != this->pacientes.end()){
            for(auto medico : this->pacientes[id].get()->getMedicos()){
                medico->removerPaciente(id);
            }
            this->pacientes.erase(id);
        }else{
            throw MessageException("fail: paciente nao encontrado");
        }
    }

    std::string showAll(){
        std::stringstream ss;

        for(auto paciente : this->pacientes){
            ss << paciente.second->toString() << "\n";
        }

        for(auto medico : this->medicos){
           ss << medico.second->toString() << "\n";
        }

        return ss.str();
    }

    void vincular(std::string medicoId, std::string pacienteId){

        if((this->pacientes.find(pacienteId) == this->pacientes.end()) || this->medicos.find(medicoId) == this->medicos.end()){
            throw MessageException("fail: paciente/medico incorreto");
        
        }else{
            auto pacientesMed = this->pacientes[pacienteId].get()->getMedicos();
            if(std::find(pacientesMed.begin(), pacientesMed.end(), this->medicos[medicoId].get()) != pacientesMed.end()){
                throw MessageException("fail: medico e paciente ja vinculados");
            }else{
                for(auto medico : this->pacientes[pacienteId].get()->getMedicos()){
                    if(medico->getClasse() == this->medicos[medicoId]->getClasse()){
                        throw MessageException("fail: ja existe outro medico com a especialidade " + this->medicos[medicoId]->getClasse());
                    }
                }

                this->medicos[medicoId]->addPaciente(this->pacientes[pacienteId].get());
                this->pacientes[pacienteId]->addMedico(this->medicos[medicoId].get());
            }
        }
    }

    void desvincular(std::string medicoId, std::string pacienteId){
        this->medicos[medicoId]->removerPaciente(this->pacientes[pacienteId]->getId());
        this->pacientes[pacienteId]->removerMedico(this->medicos[medicoId]->getId());
    }
    
};


int main() {
    Hospital hospital;

    while (true){
        std::string linha{""};
        std::string comando{""};

        // std::cout << "$";

        getline(std::cin, linha);

        std::stringstream ss(linha);

        ss >> comando;

        try{
            if(comando == "addPacs"){
            std::string temp;

            while(ss >> temp){
               int pos = temp.find("-");

               std::string paciente = temp.substr(0, pos);
               std::string diagnostico = temp.substr(pos + 1);

               hospital.addPaciente(std::make_shared<Paciente>(paciente, diagnostico));
            }

            }else if(comando == "addMeds"){
                std::string temp;

                while(ss >> temp){
                int pos = temp.find("-");

                std::string id = temp.substr(0, pos);
                std::string classe = temp.substr(pos + 1);

                hospital.addMedico(std::make_shared<Medico>(id, classe));
                }

            }else if(comando == "rmPac"){
                std::string pacId;

                ss >> pacId;

                hospital.removerPaciente(pacId);
            
            }else if(comando == "rmMed"){
                std::string medId;

                ss >> medId;

                hospital.removerMedico(medId);
            
            }else if(comando == "show"){
                std::cout << hospital.showAll();
            
            }else if(comando == "tie"){
                std::string medId;
                std::string pacId;

                ss >> medId;

                while(ss >> pacId){
                    hospital.vincular(medId, pacId);
                }
            
            }else if(comando == "untie"){
                std::string medId;
                std::string pacId;

                ss >> medId >> pacId;

            }else if(comando == "end"){
                break;
            
            }else{
                throw MessageException("fail: comando invalido");
            }
 
        }
        catch(MessageException& e){
            std::cout << e.what() << '\n';
        }
        

    }
    
}
