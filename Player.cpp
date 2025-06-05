#include <iostream> 
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Player
{


    public:
        float position;
        int x;
        int y;
        Player(int x, int y){
            this->x =x;
            this->y =y;
            sf::Texture texture;
            texture.loadFromFile("spaceShip.png");
            sprite.setTexture(texture);
        }

        sf::Sprite getSprite(){
            sprite.setPosition(x,y);
            return sprite;
        }
    private:
        
        sf::Sprite sprite;
        
};