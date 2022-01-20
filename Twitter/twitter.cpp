#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>

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

class Message{
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes;

public:
    Message(int id, std::string username, std::string msg) : id{id}, username{username}, msg{msg}{}

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
            os << *msg << "\n";
        }

        return os;
    }

    void storeUnread(Message* tweet){
        this->allMsg[tweet->getId()] = tweet;
        this->unread[tweet->getId()] = tweet;
    }

    void storeReaded(Message* tweet){
        this->allMsg[tweet->getId()] = tweet;
    }

    std::vector<Message*> getAll(){
        std::vector<Message*> temp;

        for(auto message : this->allMsg){
            temp.push_back(message.second);
        }

        return temp;
    }

    std::vector<Message*> getUnread(){
        std::vector<Message*> temp;

        for(auto message : this->unread){
            temp.push_back(message.second);
        }

        this->unread.clear();

        return temp;
    }

    Message* getTweet(int id){
        auto it = allMsg.find(id);

        if(it != allMsg.end()){ 
            return it->second;
        
        }else{
             throw MessageException("fail: tweet nao existe");
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
                os << followingSp.first << ", ";
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
                os << followersSp.first << ", ";
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
       inbox.storeReaded(tw);

        for(auto foll : this->followers){
            foll.second->getInbox()->storeUnread(tw);
        }
    }

    void unfollow(User* other){
        this->following.erase(other->username);
        other->followers.erase(this->username);
    }
};

class Controller{
    int newTwID{0};
    std::map<int, std::shared_ptr<Message>> tweets;
    std::map<std::string, std::shared_ptr<User>> users;

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
            users[username] = std::make_shared<User>(username);
        
        }else{
            throw MessageException("fail: usuario ja cadastrado");
        }
    }

    User* getUser(std::string username){
        if(users.find(username) != users.end()){
            return this->users[username].get();
        
        }else{
            throw MessageException("fail: usuario nao encontrado");
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

        std::cout << "$";

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
                for(auto msg : controller.getUser(username)->getInbox()->getUnread()){
                    std::cout << *msg << "\n";
                }
            
            }else if(comando == "end"){
                break;
            
            }else{
                throw MessageException("fail: comando invalido");
            }
        }
        catch(const MessageException& e) {
            std::cout << e.what() << '\n';
        }
    }
}