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

class Tweet{
private:
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes;
    Tweet* rt {nullptr};
    bool deleted{false};

public:
    Tweet(int id, std::string username, std::string msg) : id{id}, username{username}, msg{msg}{}

    friend std::ostream &operator<<(std::ostream& os, const Tweet& tweet){
        os << tweet.getId() << ":" << tweet.username << " (" << tweet.msg << ")";
        if((int) tweet.likes.size() > 0){
            os << "  " << "[";

            int size = 1;

            for(auto user : tweet.likes){
                if(size < (int) tweet.likes.size()){
                    os << user << ", ";

                }else{
                    os << user;
                }

                size++;
            }

            os << "]";
        }

        if(tweet.rt != nullptr){
            os << "\n\t" << *tweet.rt;
        }

        return os; 
    }

    void like(std::string username){
        likes.insert(username);
    }

    int getId() const{
        return this->id;
    }

    std::string getSender() const{
        return this->username;
    }

    std::string getMsg() const{
        return this->msg;
    }

    std::set<std::string> getLikes() const{
        return this->likes;
    }

    void setRt(Tweet* rt){
        this->rt = rt;
    }

    void setDeleted(){
        this->deleted = true;
        this->msg = "tweet deletado";
        this->username = "";
        this->likes.clear();
    }

    bool isDeleted() const{
        return this->deleted;
    }

};

class Inbox{
private:
    std::map<int, Tweet*> timeline;
    std::map<int, Tweet*> myTweets;

public:
    Inbox(){}

    friend std::ostream &operator<<(std::ostream& os, const Inbox& inbox){
        for(auto msg : inbox.getTimeline()){
            os << *msg << "\n";
        }

        return os;
    }

    std::vector<Tweet*> getTimeline() const{
        std::vector<Tweet*> temp;

        for(auto it = this->timeline.rbegin(); it != this->timeline.rend(); ++it){
            if(it->second->isDeleted() == false){
                temp.push_back(it->second);
            }
        }

        return temp;
    }

    std::vector<Tweet*> getMyTweets() const{
        std::vector<Tweet*> temp;

        for(auto it = this->myTweets.rbegin(); it != this->myTweets.rend(); ++it){
            temp.push_back(it->second);
        }

        return temp;
    }

    Tweet* getTweet(int id) const{
        auto it = timeline.find(id);

        if(it != timeline.end()){ 
            return it->second;
        
        }else{
             throw MessageException("fail: tweet nao existe");
        }
    }

    void storeInTimeline(Tweet* tweet){
        this->timeline[tweet->getId()] = tweet;
    }

    void storeInMyTweets(Tweet* tweet){
        this->myTweets[tweet->getId()] = tweet;
        this->timeline[tweet->getId()] = tweet;
    }

    void rmMsgFrom(const std::string username){
        std::vector<int> keys;

        for(auto tweet : this->timeline){
            if(tweet.second->getSender() == username){
                keys.push_back(tweet.first);
            }
        }

        for(auto key : keys){
            this->timeline.erase(key);
        }
    }

};


class User{
private:
    std::string username;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;
    Inbox inbox;

public:

    User(std::string id) : username{id} {}

    friend std::ostream &operator<<(std::ostream& os, const User& user){
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

    void unfollow(User* other){
        this->inbox.rmMsgFrom(other->username);

        this->following.erase(other->username);
        other->followers.erase(this->username);
    }

    void unfollowAll(){
        for(auto user : this->following){
            user.second->followers.erase(this->username);
        }

        this->following.clear();
    }

    void rejectAll(){
        for(auto user : this->followers){
            user.second->following.erase(this->username);
        }

        this->followers.clear();
    }

    Inbox* getInbox(){
        return &this->inbox;
    }

    void like(int tweetId){
        inbox.getTweet(tweetId)->like(this->username);
    }

    void sendTweet(Tweet* tw){
       inbox.storeInMyTweets(tw);
       inbox.storeInTimeline(tw);

        for(auto foll : this->followers){
            foll.second->getInbox()->storeInTimeline(tw);
        }
    }

};

class Controller{
private:
    int newTwID{0};
    std::map<int, std::shared_ptr<Tweet>> tweets;
    std::map<std::string, std::shared_ptr<User>> users;

    Tweet* createTweet(std::string username, std::string msg){
        auto tweet = std::make_shared<Tweet>(newTwID++, username, msg);
        this->tweets[tweet->getId()] = tweet;
        return tweet.get();
    }

public:

    Controller() {}
    
    friend std::ostream &operator<<(std::ostream& os, const Controller& controller){
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

    void rmUser(std::string username){
        User* user = this->getUser(username);
        user->unfollowAll();
        user->rejectAll();

        for(auto tweet : user->getInbox()->getMyTweets()){
            tweet->setDeleted();
        }

        this->users.erase(username);
    }

    User* getUser(std::string username){
        if(users.find(username) != users.end()){
            return this->users[username].get();
        
        }else{
            throw MessageException("fail: usuario nao encontrado");
        }

    }

    void sendTweet(std::string username, std::string msg){
        getUser(username)->sendTweet(createTweet(username, msg));
    }

    void sendRt(std::string username, int id, std::string msg){
        Tweet* rt = getUser(username)->getInbox()->getTweet(id);
        Tweet* tw = createTweet(username, msg);

        tw->setRt(rt);
        getUser(username)->sendTweet(tw);
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

            if(comando == "add"){
                std::string username;

                ss >> username;

                controller.addUser(username);
            
            }else if(comando == "rm"){
                std::string username;

                ss >> username;

                controller.rmUser(username);
            }
            else if(comando == "show"){
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
            
            }else if(comando == "rt"){
                std::string username;
                int id;
                std::string msg;

                ss >> username >> id;

                getline(ss, msg);

                controller.sendRt(username, id, msg.substr(1));

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

    return 0;
}