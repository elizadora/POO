#include <SFML/Graphics.hpp>
#include <iostream>


void setSize(sf::Sprite& sprite, int width, int height, bool piupiu){
    auto dim = sprite.getLocalBounds();
    if(piupiu){
        sprite.setScale((float) (width - 50) / dim.width, (float) (height - 50) / dim.height);
    }else{
        sprite.setScale((float) width / dim.width, (float) height / dim.height);
    }
}



struct Entity
{
    //atributos

   int x {0};
   int y {0};
   int step {0};

    sf::Sprite sprite;

    //construtor
    Entity(int x, int y, int step, sf::Texture& texture){
        this->x = x;
        this->y = y;
        this->step = step;
        this->sprite.setTexture(texture);
    }

    //metodos utilizados

    void draw(sf::RenderWindow& window, bool piupiu){
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step, piupiu);
        window.draw(this->sprite);
    }

};

struct Board
{
    //atributos
    int nc {0};
    int nl {0};
    int step {0};
    sf::Sprite sprite;
    sf::RectangleShape rectangle;

    Board(int nc, int nl, int step, sf::Texture& texture){
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, nc * step, nl * step, false);
        this->sprite.setPosition(0, 0);

        //configurações retangulo
        this->rectangle.setSize(sf::Vector2f(step, step));
        this->rectangle.setFillColor(sf::Color::Transparent);
        this->rectangle.setOutlineColor(sf::Color::Black);
        this->rectangle.setOutlineThickness(1);

    }

    void drawBackground(sf::RenderWindow& window){
        window.draw(this->sprite);
        for (int i = 0; i < nc; i++)
        {
           for (int j = 0; j < nl; j++)
           {
               rectangle.setPosition(i * step, j * step);
               window.draw(rectangle);
           }
           
        }
        
    }

};


void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys){
    if(key == move_keys[0]){
        entity.x --;
    }else if(key == move_keys[1]){
        entity.y--;
    }else if(key == move_keys[2]){
        entity.x++;
    }else if(key == move_keys[3]){
        entity.y++;
    }
}

sf::Texture loadTexture(std::string path){
    sf::Texture texture;
    if(!texture.loadFromFile(path)){
        std::cout << "Errro ao carregar textura\n";
        exit(1);
    }

    return texture;
}


int main()
{
    //Criando texturas
    sf::Texture backgroundText {loadTexture("img\\back.jpg")};
    sf::Texture piupiuText{loadTexture("img\\piupiu.png")};
    sf::Texture frajolaText{loadTexture("img\\frajola.png")};
    
    const int STEP {100};

    //Criando as entidades
    Entity piupiuSA(3, 3, STEP, piupiuText);
    Entity frajolaSA(1, 1, STEP, frajolaText);

    Board board (7, 5, STEP, backgroundText);


   sf::RenderWindow window(sf::VideoMode(board.nc * STEP, board.nl * STEP), "Frajola e PiuPiu Game");

    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                     window.close();       
            }else if(event.type == sf::Event::KeyPressed){
                moveEntity(event.key.code, piupiuSA, {sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S});
                 moveEntity(event.key.code, frajolaSA, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down});
            }
           
        }

        window.clear();

        //desenhando background
        board.drawBackground(window);

        // desenhando a entidade
        piupiuSA.draw(window, true);
        frajolaSA.draw(window, false);

        window.display();
    }

    return 0;
}