#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <memory>

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
    std::string diagnostico;
    std::map<std::string, IMedico*> medicos;
    std::string sender;

public:
    Paciente(std::string sender, std::string diagnostico) : sender{sender}, diagnostico{diagnostico} {}
    
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
        return this->sender;
    }

    std::vector<IMedico*> getMedicos() override{
        std::vector<IMedico*> temp;

        for(auto medico : this->medicos){
            temp.push_back(medico.second);
        }

        return temp;
    }

    void removerMedico(std::string medicoId) override{}
};

class Medico : public IMedico{
private:
    std::string classe;
    std::map<std::string, IPaciente*> pacientes;
    std::string sender;

public:
    Medico(std::string sender, std::string classe) : sender{sender}, classe{classe} {}

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
        return this->sender;
    }

    std::vector<IPaciente*> getPacientes() override{
        std::vector<IPaciente*> temp;

        for(auto paciente : this->pacientes){
            temp.push_back(paciente.second);
        }

        return temp;
    }

    void removerPaciente(std::string pacienteId) override{}
};

class Hospital{
private:
    std::map<std::string, std::shared_ptr<IPaciente>> pacientes;
    std::map<std::string, std::shared_ptr<IMedico>> medicos;

public:
    Hospital(){}

    void addMedico(std::shared_ptr<IMedico> medico){
        medicos[medico->getId()] = medico;
    }

    void addPaciente(std::shared_ptr<IPaciente> paciente){
        pacientes[paciente->getId()] = paciente;
    }

    void removerMedico(std::string sender) {}

    void removerPaciente(std::string sender) {}

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
        IPaciente* pac = this->pacientes[pacienteId].get();
        this->medicos[medicoId]->addPaciente(pac);

        IMedico* med = this->medicos[medicoId].get();
        this->pacientes[pacienteId]->addMedico(med);
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

               std::string sender = temp.substr(0, pos);
               std::string classe = temp.substr(pos + 1);

               hospital.addMedico(std::make_shared<Medico>(sender, classe));
            }

        }else if(comando == "show"){
            std::cout << hospital.showAll();
        
        }else if(comando == "tie"){
            std::string medId;
            std::string pacId;

            ss >> medId;

            while(ss >> pacId){
                hospital.vincular(medId, pacId);
            }
        }


    }
    
}
