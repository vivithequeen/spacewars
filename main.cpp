#include <iostream> 
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <optional>
#include "Player.cpp"
using namespace std;

sf::Vector2u screenRes;
sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Space Wars");


int main()
{
    
    screenRes = window.getSize();
    window.setFramerateLimit(1);
    Player p(1,1);
    

    while (window.isOpen())
    {


        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(); 
        window.draw(p.getSprite());

        window.display();
    }
}