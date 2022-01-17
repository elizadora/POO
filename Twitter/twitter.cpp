#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <sstream>

class Message{
    int id;
    std::set<std::string> likes;
    std::string msg;
    std::string username;

public:
    Message(int id = 0, std::string username = "", std::string msg = ""){
        this->id = id;
        this->username = username;
        this->msg = msg;

    }

    friend std::ostream &operator<<(std::ostream& os, const Message& message){
        os << message.getId() << ":" << message.username << " (" << message.msg << ")";
        if((int) message.likes.size() > 0){
            os << "  " << "[";

            int size = 1;

            for(auto user : message.likes){
                if(size < (int) message.likes.size()){
                    os << user << ", ";

                }else{
                    os << user;
                }

                size++;
            }

            os << "]";
        }

        return os; 
    }

    void like(std::string username){
        likes.insert(username);
    }

    int getId() const{
        return this->id;
    }

};

class Inbox{
    std::map<int, Message*> unread;
    std::map<int, Message*> allMsg;

public:
    Inbox(){}

    friend std::ostream &operator<<(std::ostream& os, Inbox& inbox){
        for(auto msg : inbox.getAll()){
            os << *msg.second << "\n";
        }

        return os;
    }

    void receiveNew(Message* tweet){
        this->allMsg[tweet->getId()] = tweet;
        this->unread[tweet->getId()] = tweet;
    }

    // void store(Message* tweet){

    // }

    std::map<int, Message*> getAll(){
        return this->allMsg;
    }

    std::map<int, Message*>* getUnread(){
        return &this->unread;
    }

    Message* getTweet(int id){
        auto it = allMsg.find(id);

        if(it != allMsg.end()){ 
            return it->second;
        
        }else{
             throw std::runtime_error("fail: tweet nao existe");
        }
    }

};


class User{
    std::string username;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;
    Inbox inbox;

public:

    User(std::string id) : username{id} {}

    friend std::ostream &operator<<(std::ostream& os, User& user){
        os << user.username << "\n";
        os << "\tseguidos\t[";
        int size = 1;

        for(auto followingSp : user.following){
            if(size < (int) user.following.size()){
                os << followingSp.first << ",";
            }else{
                 os << followingSp.first; 
            }

            size++;
        }

        os << "]\n";
        
        os << "\tseguidores\t[";
        size = 1;

        for(auto followersSp : user.followers){
            if(size < (int) user.followers.size()){
                os << followersSp.first << ",";
            }else{
                 os << followersSp.first; 
            }

            size++;
        }

        os << "]\n";

        return os;
    }

    void follow(User* other){
        this->following[other->username] = other;
        other->followers[this->username] = this;
    }

    Inbox* getInbox(){
        return &this->inbox;
    }

    void like(int tweetId){
        inbox.getTweet(tweetId)->like(this->username);
    }

    void sendTweet(Message* tw){
       inbox.receiveNew(tw);

        for(auto foll : this->followers){
            foll.second->getInbox()->receiveNew(tw);
        }
    }

    void unfollow(User* other){
        this->following.erase(other->username);
        other->followers.erase(this->username);
    }
};

class Controller{
    int newTwID{0};
    std::map<int, Message*> tweets;
    std::map<std::string, User*> users;

public:

    Controller() {}
    
    friend std::ostream &operator<<(std::ostream& os, Controller& controller){
        for(auto user : controller.users){
            os << *user.second;
        }

        return os;
    }

    void addUser(std::string username){
        if(users.find(username) == users.end()){
            users[username] = new User(username);
        
        }else{
            throw std::runtime_error("fail: usuario ja cadastrado");
        }
    }

    User* getUser(std::string username){
        auto it = users.find(username);

        if(it != users.end()){
            return it->second;
        
        }else{
            throw std::runtime_error("fail: usuario nao encontrado");
        }

    }

    void sendTweet(std::string username, std::string msg){
        getUser(username)->sendTweet(new Message(newTwID, username, msg));
        newTwID++;
    }

};


int main(){
    Controller controller;

    while(true){
        std::string linha{""};
        std::string comando{""};

        // std::cout << "$";

        getline(std::cin, linha);

        std::stringstream ss(linha);

        ss >> comando;

        try{

            if(comando == "addUser"){
                std::string username;

                ss >> username;

                controller.addUser(username);
            
            }else if(comando == "show"){
                std::cout << controller;
            
            }else if(comando == "follow"){
                std::string user;
                std::string other;

                ss >> user >> other;

                controller.getUser(user)->follow(controller.getUser(other));
            
            }else if(comando == "twittar"){
                std::string username;
                std::string msg;

                ss >> username;

                getline(ss, msg);

                controller.sendTweet(username, msg.substr(1));
            
            }else if(comando == "timeline"){
                std::string username;

                ss >> username;

                std::cout << *controller.getUser(username)->getInbox();
            
            }else if(comando == "like"){
                std::string username;
                int idMsg;

                ss >> username >> idMsg;

                controller.getUser(username)->like(idMsg);
            
            }else if(comando == "unfollow"){
                std::string user;
                std::string other;

                ss >> user >> other;

                controller.getUser(user)->unfollow(controller.getUser(other));
            
            }else if(comando == "unread"){
                std::string username;

                ss >> username;
                for(auto msg : *controller.getUser(username)->getInbox()->getUnread()){
                    std::cout << *msg.second << "\n";
                }

                controller.getUser(username)->getInbox()->getUnread()->clear();
            
            }else{
                break;
            }
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
        

    }
}