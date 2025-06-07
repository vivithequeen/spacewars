#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <optional>
#include "OutLineCollition.cpp"
#include "Player.cpp"
#include "Sun.cpp"

#include <cstdlib>
#include <ctime>

using namespace std;

const int screenWidth = 1080;
sf::RenderWindow window(sf::VideoMode({screenWidth, screenWidth}), "Space Wars");

const int amountOfStars = 100;

float starsLocationsx[amountOfStars];
float starsLocationsy[amountOfStars];

Sun sun;
OutLineCollition colliders[360];
sf::SoundBuffer zap;
sf::Texture t;
Laser lasers[1024];

Player p(screenWidth/2,100);

sf::Vector2i rotateVector(sf::Vector2i v, float r){
    r = r*M_PI/180.0;
    return sf::Vector2i(v.x*cos(r) - v.y*sin(r), v.x*sin(r) + v.y*cos(r));
}
sf::Vector2f rotateVector(sf::Vector2f v, float r){
    r = r*M_PI/180.0;
    return sf::Vector2f(v.x*cos(r) - v.y*sin(r), v.x*sin(r) + v.y*cos(r));
}
void initStars(){
    srand(time(0));
    

    for(int i = 0; i< amountOfStars;i++)
    {
        float x = (static_cast<float>(rand() % 100) / 100.0f) * 1920;
        float y = (static_cast<float>(rand() % 100) / 100.0f) * 1080;
        starsLocationsx[i] = x;
        starsLocationsy[i] = y;
    }
}

void drawStars(){
    sf::Texture starTexture;
    starTexture.loadFromFile("textures/star.png");
    for(int i = 0; i< amountOfStars;i++)
    {

        sf::Sprite s;
        s.setPosition(starsLocationsx[i], starsLocationsy[i]);
        s.setTexture(starTexture);
        s.setScale(2,2);
        window.draw(s);

    }
}
void setColliders(){

    
    for(int i = 0; i < 360;i++){
        sf::Vector2i s(0,screenWidth/2);
        sf::Vector2i v = rotateVector(s, i);
        colliders[i].setPosition(v + sf::Vector2i(540,540));
        colliders[i].id = i;

    }
}
int findEmptyLaser(){
    for(int i = 0; i < sizeof(lasers);i++){
        if(lasers[i].isEmpty){
            return i;
        }
    }
    cout<<"ah fuck";
    return -1;
}
void drawColliders(){
    for(int i = 0; i < 360;i++){
        window.draw(colliders[i].debugDraw());
        
    }
}
bool fireLaser(){
    sf::Vector2f rv(0,-10);
    sf::Vector2f r = rotateVector(rv, p.rotation);
    //cout<<r.x;
    lasers[findEmptyLaser()] = Laser(p.x,p.y,p.rotation, r.x,r.y);
    return true;
}



int main()
{

    setColliders();
    initStars();
    if(!zap.loadFromFile("audio/laserShoot.wav")){return -1;}
    if(!t.loadFromFile("textures/outline.png")){return -1;}

    window.setFramerateLimit(60);
    
    
    Collider c1(0,0,10,32);
    Collider c2(0,0,10,10);
    cout<<c2.checkCollition(c1);
    bool lmbPressed = false;


    while (window.isOpen())
    {
        p.teleportCoolDown-=1;
        p.laserCoolDown-=1;

        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
        {
            // left key is pressed: move our character
            p.turnLeft();

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
        {
            // left key is pressed: move our character
            p.turnRight();

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)){ 
            p.forwardsImpulse(1);
            
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            if(p.laserCoolDown<0)
            {
                fireLaser();
                p.laserCoolDown=10;
            }
            
        }

        for(int i = 0; i < 360;i++){
            if(colliders[i].collider.checkCollition(p.collider) and p.teleportCoolDown < 0){
                p.setPosition(colliders[colliders[i].getOpposite()].x,colliders[colliders[i].getOpposite()].y);

                p.teleportCoolDown = 25;
            }

        }
        if(sun.checkCollition(p.x,p.y)){
            sf::Vector2f nv =sf::Vector2f(sun.x,sun.y) - sf::Vector2f(p.x,p.y);
            nv.x/=1300;
            nv.y/=1300;
            p.addVelocity(nv);
        }

        window.clear(); 

        sf::RectangleShape r(sf::Vector2f(screenWidth,screenWidth));
        r.setFillColor(sf::Color(13,43,69));
        window.draw(r);
        
        
        sf::Sprite outline(t);
        outline.scale(4,4);
        drawStars();
        window.draw(sun.debugDraw(p));
        

        p.updatePosition();
        window.draw(p.getSprite());
        window.draw(outline);
        window.draw(sun.getSprite());
        for(int i = 0; i < 1024;i++)
        {
            if(!lasers[i].isEmpty)
            {
                if(lasers[i].update()){
                    lasers[i] = Laser();
                }
                window.draw(lasers[i].getSprite());
            }
        }


        window.display();
    }
}