#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Collider.cpp"
#include "Laser.cpp"
using namespace std;
#ifndef PLAYER
#define PLAYER

class Player 
{
    public:
        sf::Texture texture;

        Collider collider;
        const int MAXSPEED = 6;

        float rotation;
        
        float x;
        float y;
        float teleportCoolDown;
        float laserCoolDown;
        sf::Vector2f velocity;
        
        Player(int x, int y){
            laserCoolDown = -1;
            teleportCoolDown = -1;
            collider = Collider(x,y,16,16);
            this->x =x;
            this->y =y;

            texture.loadFromFile("textures/spaceShip.png");
            sprite.setTexture(texture);
            sprite.scale(2,2);
            sprite.setOrigin(8,8);
            rotation = 0;
        }

        void turnLeft(){
            rotation-=2;
        }

        void turnRight(){
            rotation+=2;
        }

        sf::Vector2f rotateVector(sf::Vector2f v, float r){
            r = r*M_PI/180.0;
            return sf::Vector2f(v.x*cos(r) - v.y*sin(r), v.x*sin(r) + v.y*cos(r));
        }

        float getVectorLength(sf::Vector2f v){
            return(v.x * v.x + v.y * v.y );
        }
        sf::Vector2f getNormalizedVector(sf::Vector2f v){
            float vlength = getVectorLength(v);
            return sf::Vector2f(v.x / vlength, v.y / vlength);
        }
        void addVelocity(sf::Vector2f v){
            velocity.x+=v.x;
            velocity.y+=v.y;
        }
        void forwardsImpulse(int strength)
        {
            sf::Vector2f v(0,-0.1);
            v = rotateVector(v, rotation);
            

            velocity.x+=v.x * strength;
            velocity.y+=v.y * strength;



        }
        void setPosition(int x, int y){
            this->x =x;
            this->y =y;
        }
        void updatePosition(){
            if(getVectorLength(velocity) > MAXSPEED){
                sf::Vector2f vc(velocity.x,velocity.y);
                velocity.x*= MAXSPEED/getVectorLength(vc);
                velocity.y*= MAXSPEED/getVectorLength(vc);
            }
            int index = 0;
            x+=velocity.x;
            y+=velocity.y;
            collider.updatePosition(x,y);
        }

        sf::Sprite getSprite(){

            
            sprite.setRotation(rotation);
            sprite.setPosition(x,y);
            return sprite;
        }

    private:
        
        sf::Sprite sprite;
        
};
#endif