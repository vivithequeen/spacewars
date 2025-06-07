#include <iostream>
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Collider.cpp"
#include "Player.cpp"
using namespace std;
class Sun
{
public:
    int x, y;
    sf::Texture texture;
    const int r = 1080/8;

    Sun()
    {
        x = 1080 / 2;
        y = 1080 / 2;
        texture.loadFromFile("textures/sun.png");
        sprite.setTexture(texture);
        sprite.scale(2,2);
        sprite.setOrigin(3,3);
    }        
    float getVectorLength(sf::Vector2f v){
        return(v.x * v.x + v.y * v.y );
    }
    sf::Vector2f getNormalizedVector(sf::Vector2f v){
        float vlength = getVectorLength(v);
        return sf::Vector2f(v.x / vlength, v.y / vlength);
    }
    bool checkCollition(int cx, int cy)
    {        
        return ((cx-x) * (cx-x)) + ((cy - y) * (cy - y)) < r*r;
    }

    sf::Sprite getSprite(){
        sprite.setPosition(x,y);
        
        return sprite;
    }

    sf::CircleShape debugDraw(Player p){
        sf::CircleShape c;
        c.setRadius(r);
        c.setPosition(x-r,y-r);
        c.setFillColor(checkCollition(p.x, p.y) ? sf::Color::Green : sf::Color::Red);
    
        return c;
    }
    private:
        
        sf::Sprite sprite;
};