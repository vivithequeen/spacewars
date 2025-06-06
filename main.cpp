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

#include <cstdlib>
#include <ctime>

using namespace std;

const int screenWidth = 1080;
sf::RenderWindow window(sf::VideoMode({screenWidth, screenWidth}), "Space Wars");

const int amountOfStars = 100;

float starsLocationsx[amountOfStars];
float starsLocationsy[amountOfStars];


OutLineCollition colliders[360];

sf::Vector2i rotateVector(sf::Vector2i v, float r){
    r = r*M_PI/180.0;
    return sf::Vector2i(v.x*cos(r) - v.y*sin(r), v.x*sin(r) + v.y*cos(r));
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
    starTexture.loadFromFile("star.png");
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
void drawColliders(){
    for(int i = 0; i < 360;i++){
        window.draw(colliders[i].getSprite());
        
    }
}
int tpCooldown =0;
int main()
{
    setColliders();
    initStars();

    window.setFramerateLimit(60);
    Player p(screenWidth/2,screenWidth/2);
    Collider c1(0,0,10,32);
    Collider c2(0,0,10,10);
    cout<<c2.checkCollition(c1);

    while (window.isOpen())
    {
        tpCooldown-=1;

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
            p.fireLazer();
        }
        for(int i = 0; i < 360;i++){
            if(colliders[i].collider.checkCollition(p.collider) and tpCooldown < 0){
                p.setPosition(colliders[colliders[i].getOpposite()].x,colliders[colliders[i].getOpposite()].y);

                tpCooldown = 25;
            }

        }


        window.clear(); 
        sf::Texture t;
        t.loadFromFile("outline.png");
        sf::Sprite outline(t);
        drawStars();
        

        p.updatePosition();
        window.draw(p.getSprite());
        window.draw(outline);




        window.display();
    }
}