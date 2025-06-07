#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Collider.cpp"
using namespace std;
#ifndef LASER
#define LASER
class Laser
{
    public:
    float x, y;
    float vx, vy;
    bool exists = true;
    float rotation;
    sf::Vector2f distanceV;
    sf::Texture texture;
    Laser()
    {
        x=0;
        y=0;
    }

    Laser(int x, int y,float r, float vx, float vy){

        texture.loadFromFile("textures/laser.png");
        sprite.setTexture(texture);
        sprite.setOrigin(1.5,3);
        sprite.setRotation(r);
        this -> x  =x;
        this -> y = y;
        this -> vx  =10;//vx;
        this -> vy = 10;//vy;
        rotation = r;
        

    }

    bool checkInBounds(){
        return(x > 0 && y > 0 && x < 1080 && y < 1080);
    }
    void update(){
        cout<<vx;
        x+=vx;
        y+=vy;
    }
    sf::Sprite getSprite(){
        sprite.setPosition(x,y);
        return sprite;
    }
    private:
    sf::Sprite sprite;
};
#endif