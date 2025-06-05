#include <iostream> 
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

class Player 
{


    public:
        sf::Texture texture;


        float rotation;

        int x;
        int y;
        sf::Vector3f velocity;
        Player(int x, int y){
            this->x =x;
            this->y =y;

            texture.loadFromFile("spaceShip.png");
            sprite.setTexture(texture);
            sprite.scale(2,2);
            sprite.setOrigin(16,16);
            rotation = 0;
        }
        void turnLeft(){
            rotation-=1;
        }

        void turnRight(){
            rotation+=1;
        }

        void forwardsImpulse()
        {
            sf::Vector2f v(0,0.1);
            sf::Vector2f nv;
            nv.x = (v.x*cos(rotation) - v.y*sin(rotation));
            nv.y = (v.x*sin(rotation) + v.y*cos(rotation));
            velocity.x+=nv.x;
            velocity.y+=nv.y;
            cout<<velocity.x <<" "<< velocity.y<<"\n";
        }

        void updatePosition(){
            x+=velocity.x;
            y+=velocity.y;
        }

        sf::Sprite getSprite(){
            
            
            sprite.setRotation(rotation);
            sprite.setPosition(x,y);
            return sprite;
        }
    private:
        
        sf::Sprite sprite;
        
};