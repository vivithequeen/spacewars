#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <optional>
#include "Player.cpp"
#include <cstdlib>
#include <ctime>
using namespace std;

sf::Vector2u screenRes;
sf::RenderWindow window(sf::VideoMode({1080, 1080}), "Space Wars");
const int amountOfStarts = 100;
float starsLocationsx[amountOfStarts];
float starsLocationsy[amountOfStarts];




void initStars(){
    srand(time(0));
    

    for(int i = 0; i< amountOfStarts;i++)
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
    for(int i = 0; i< amountOfStarts;i++)
    {

        sf::Sprite s;
        s.setPosition(starsLocationsx[i], starsLocationsy[i]);
        s.setTexture(starTexture);
        s.setScale(2,2);
        window.draw(s);

    }
}
int main()
{

    initStars();
    screenRes = window.getSize();
    window.setFramerateLimit(60);
    Player p(400,400);
    

    while (window.isOpen())
    {


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
            p.forwardsImpulse();
            
        }

        window.clear(); 
        sf::Texture t;
        t.loadFromFile("outline.png");
        sf::Sprite outline(t);
        drawStars();
        window.draw(outline);

        
        p.updatePosition();
        window.draw(p.getSprite());
        


        window.display();
    }
}