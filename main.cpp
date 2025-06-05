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
sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Space Wars");

sf::Vector2f starsLocations[40];
sf::Texture starTexture;

void initStars(){
    srand(time(0));
    

    for(sf::Vector2f s : starsLocations)
    {
        float x = (static_cast<float>(rand() % 100) / 100.0f) * 1920;
        float y = (static_cast<float>(rand() % 100) / 100.0f) * 1080;
        s.x = x;
        s.y = y;
    }
}

void drawStars(){
    for(sf::Vector2f l : starsLocations)
    {
        sf::Sprite s;
        s.setPosition(l);
        
        window.draw(s);

    }
}
int main()
{
    starTexture.loadFromFile("star.png");
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

        p.updatePosition();
        window.draw(p.getSprite());
        drawStars();
        window.draw(stars[0]);

        window.display();
    }
}