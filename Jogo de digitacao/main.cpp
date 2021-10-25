#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional> //salvar functions como variaveis


struct Background{
     sf::RenderWindow& window;
     sf::Texture texture;

     Background(sf::RenderWindow& window) : window{window}{
         if(!texture.loadFromFile("src\\background.png")){
             std::cout << "Erro ao carregar background";
         }
     }

     void draw(){
         static sf::Sprite sprite;
         sprite.setTexture(texture);
         sprite.setPosition(0,0);

         auto dim = sprite.getLocalBounds();

         sprite.setScale((float) window.getSize().x / dim.width, (float) window.getSize().y / dim.height);

         this->window.draw(sprite);
     }
};

struct Pincel {
    sf::Font font;
    sf::Text text;
    sf::RenderWindow& window;

    //construtor de Pincel
    Pincel(sf::RenderWindow& window) : window{window}{
        if(!font.loadFromFile("src\\Minecraft.ttf")){
            std::cout << "Erro ao carregar a fonte\n";
        }

        text.setFont(font);
    }

    void write(std::string strText, int x, int y, int size, sf::Color color){
        text.setString(strText);
        text.setCharacterSize(size);
        text.setPosition(x, y);
        text.setFillColor(color);
        window.draw(text);
    }

};

struct Bubble {
    int x;
    int y;
    char letter;
    int speed;

    //atributo geral das bolhas
    static const int radius {15};
    bool alive {true};

    //construtor de Bubble
    Bubble(int x, int y, char letter, int speed) : x{x}, y{y}, letter{letter}, speed{speed}{
    }


    void update(){
        this->y += this->speed;
    }

    void draw(sf::RenderWindow& window){
        static Pincel pincel(window);
        sf::CircleShape bubble(Bubble::radius);
        bubble.setPosition(x, y);
        bubble.setFillColor(sf::Color{56, 129, 224});
        window.draw(bubble);
        pincel.write(std::string(1, letter), x + 0.5 * Bubble::radius, y, Bubble::radius * 1.5, sf::Color{237, 230, 227});
    }

};

struct Board{

    sf::RenderWindow& window;
    std::vector<Bubble> bubbles;
    Pincel pincel;
    Background back;
    //placar
    int hits{0};
    int misses{0};

    Board(sf::RenderWindow& window) : window{window}, pincel{window}, back{window}{
    }

    void update(){
        if(this->checkNewBubble()){
            this->addNewBubble();
        }
        for(Bubble& bubble : bubbles){
            bubble.update();
        }

        this->markMisses();
        this->removeDeadBubbles();
    }

    void removeDeadBubbles(){
        std::vector<Bubble> alives;
        for(Bubble& bubble : bubbles){
            if(bubble.alive){
                alives.push_back(bubble);
            }
        }

        this->bubbles = alives;
    }

    void markMisses(){
        for(Bubble& bubble : bubbles){
            if(bubble.y + 2 * Bubble::radius > (int) this->window.getSize().y){
                if(bubble.alive){
                    bubble.alive = false;
                    this->misses++;
                }
            }
        }
    }

    void markHits(char letter){
        for(Bubble& bubble : bubbles){
            if(bubble.letter == letter){
                bubble.alive = false;
                this->hits++;
                break;
            }
        }
    }

    bool checkNewBubble(){
        static const int newBubbleTimeOut{60};
        static int newBubbleTimer{0};

        newBubbleTimer--;

        if(newBubbleTimer <= 0){
            newBubbleTimer = newBubbleTimeOut;
            return true;
        }

        return false;
    }

    void addNewBubble(){
        int x = rand() % ((int) this->window.getSize().x - 2 * Bubble::radius);
        int y = -2 * Bubble::radius;
        int speed = rand() % 3 + 1;
        char letter = rand() % 26 + 'A';
        bubbles.push_back(Bubble(x, y, letter, speed));
    }


    void draw(){
        
        back.draw();
        pincel.write("Hits: " + std::to_string(this->hits) + " Misses: " + std::to_string(this->misses), 10, 10, 20, sf::Color::Black);
        pincel.write("Size: " + std::to_string(this->bubbles.size()), 10, 30, 20, sf::Color::Black);

        for(Bubble& bubble : bubbles){
            bubble.draw(window);
        }
    }

};

struct Game {
    sf::RenderWindow window;
    Board board;
    std::function<void()> onUpdate;
    sf::Image iconfinder;

    //construtor do Game
    Game() : window(sf::VideoMode(800, 600), "Jogo das Bolhas"), board{window}{
        this->onUpdate = [&](){
            this->gameplay();
        };
        iconfinder.loadFromFile("src\\mainicon.png");
        window.setFramerateLimit(60);
        window.setIcon(iconfinder.getSize().x, iconfinder.getSize().y, iconfinder.getPixelsPtr());
    }


    void processEvents(){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }else if(event.type == sf::Event::TextEntered){
                char code = static_cast<char>(event.text.unicode);
                code = toupper(code);
                board.markHits(code);
            }
        }
    }

    void gameplay(){
        board.update();
        window.clear(sf::Color::Black);
        board.draw();
        window.display();

        if(board.misses > 10){
            this->onUpdate = [&](){
                this->gameover();
            };
        }
    }

    void gameover(){
       static Pincel pincel(window);
       window.clear(sf::Color::Red);
       pincel.write("Game Over", 500, 500, 50, sf::Color::Black);
       window.display();
    }
    //loop principal
    void mainLoop(){
        while(window.isOpen()){
            processEvents();
            onUpdate();
        }
    }
};


int main(){
    Game game;
    game.mainLoop();

    return 0;
    
}