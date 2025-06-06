#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


using namespace std;

class OutLineCollition
{
    public:
    int x;
    int y;
    OutLineCollition(){

    }


    void setPosition(sf::Vector2i pos){
        x =pos.x;
        y =pos.y;
    }
    sf::RectangleShape getSprite(){
            
        sf::RectangleShape r(sf::Vector2f(4,4));
        r.setOrigin(2,2);
        r.setFillColor(sf::Color::Red);
        r.setPosition(x,y);
        return r;
    }
};