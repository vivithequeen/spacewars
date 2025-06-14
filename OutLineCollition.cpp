#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Collider.cpp"

using namespace std;


class OutLineCollition
{
    public:
    
        Collider collider;
        int x;
        int y;
        int id;
        OutLineCollition(){
            
        }


        void setPosition(sf::Vector2i pos){
            x =pos.x;
            y =pos.y;
            collider = Collider(x,y,4,4);
        }
        sf::RectangleShape debugDraw(){
            
            sf::RectangleShape r(sf::Vector2f(4,4));
            r.setOrigin(2,2);
            r.setFillColor(sf::Color::Red);
            r.setPosition(x,y);
            return r;
        }
        int getOpposite()
        {
            int opp = id - 180;
            if(opp < 0){
                opp+=360;
            }
            return opp;
        }
};