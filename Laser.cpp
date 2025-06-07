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
    bool isEmpty;
    float x, y;
    float vx, vy;

    float rotation;
    sf::Vector2f distanceV;
    sf::Texture texture;
    Laser()
    {
        isEmpty = true;
        x=0;
        y=0;
    }

    Laser(int x, int y,float r, float vx, float vy){
        isEmpty = false;
        texture.loadFromFile("textures/laser.png");
        sprite.setTexture(texture);
        sprite.setOrigin(1.5,3);
        sprite.setRotation(r);
        this -> x  =x;
        this -> y = y;
        this -> vx  =vx;//vx;
        this -> vy = vy;//vy;
        rotation = r;
        

    }
    void addVelocity(sf::Vector2f v){
        vx += v.x;
        vy += v.y;
    }
    bool checkInBounds(){
        return(x > 0 && y > 0 && x < 1080 && y < 1080);
    }
    bool update(){
        if(checkInBounds())
        {
            x+=vx;
            y+=vy;
            return false;
        }
        else{
            return true;
        }
    }
    sf::Sprite getSprite(){
        sprite.setPosition(x,y);
        return sprite;
    }
    private:
    sf::Sprite sprite;
};
#endif