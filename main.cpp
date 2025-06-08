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
sf::Texture s;
Laser lasers[1024];
sf::Font font;
enum
{
    MAIN_MENU = 0,
    GAME = 1,
    P1WIN = 2,
    P2WIN = 3,
};
int gameStatus = MAIN_MENU;
Player p1(screenWidth / 2, 128, true);
Player p2(screenWidth / 2, 1080 - 128, false);

sf::Vector2i rotateVector(sf::Vector2i v, float r)
{
    r = r * M_PI / 180.0;
    return sf::Vector2i(v.x * cos(r) - v.y * sin(r), v.x * sin(r) + v.y * cos(r));
}
sf::Vector2f rotateVector(sf::Vector2f v, float r)
{
    r = r * M_PI / 180.0;
    return sf::Vector2f(v.x * cos(r) - v.y * sin(r), v.x * sin(r) + v.y * cos(r));
}
void initStars()
{
    srand(time(0));

    for (int i = 0; i < amountOfStars; i++)
    {
        float x = (static_cast<float>(rand() % 100) / 100.0f) * 1920;
        float y = (static_cast<float>(rand() % 100) / 100.0f) * 1080;
        starsLocationsx[i] = x;
        starsLocationsy[i] = y;
    }
}

void drawStars()
{
    sf::Texture starTexture;
    starTexture.loadFromFile("textures/star.png");
    for (int i = 0; i < amountOfStars; i++)
    {

        sf::Sprite s;
        s.setPosition(starsLocationsx[i], starsLocationsy[i]);
        s.setTexture(starTexture);
        s.setScale(2, 2);
        window.draw(s);
    }
}
void setColliders()
{

    for (int i = 0; i < 360; i++)
    {
        sf::Vector2i s(0, screenWidth / 2);
        sf::Vector2i v = rotateVector(s, i);
        colliders[i].setPosition(v + sf::Vector2i(540, 540));
        colliders[i].id = i;
    }
}
int findEmptyLaser()
{
    for (int i = 0; i < 1024; i++)
    {
        if (lasers[i].isEmpty)
        {
            return i;
        }
    }

    return -1;
}
void drawColliders()
{
    for (int i = 0; i < 360; i++)
    {
        window.draw(colliders[i].debugDraw());
    }
}
float getVectorLength(sf::Vector2f v)
{
    return (v.x * v.x + v.y * v.y);
}
sf::Vector2f getNormalizedVector(sf::Vector2f v)
{
    float vlength = getVectorLength(v);
    return sf::Vector2f(v.x / vlength, v.y / vlength);
}
bool p1fireLaser()
{
    sf::Vector2f rv(0, -5);
    sf::Vector2f r = rotateVector(rv, p1.rotation);
    // cout<<r.x;
    lasers[findEmptyLaser()] = Laser(p1.x, p1.y, p1.rotation, r.x, r.y);
    return true;
}
bool p2fireLaser()
{
    sf::Vector2f rv(0, -5);
    sf::Vector2f r = rotateVector(rv, p2.rotation);
    // cout<<r.x;
    lasers[findEmptyLaser()] = Laser(p2.x, p2.y, p2.rotation, r.x, r.y);
    return true;
}
void p1Inputs()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left))
    {
        // left key is pressed: move our character
        p1.turnLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right))
    {
        // left key is pressed: move our character
        p1.turnRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))
    {
        p1.forwardsImpulse(1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down))
    {
        if (p1.laserCoolDown < 0)
        {
            p1fireLaser();
            p1.laserCoolDown = 30;
        }
    }
}
void p2Inputs()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
    {
        // left key is pressed: move our character
        p2.turnLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
    {
        // left key is pressed: move our character
        p2.turnRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
    {
        p2.forwardsImpulse(1);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
    {
        if (p2.laserCoolDown < 0)
        {
            p2fireLaser();
            p2.laserCoolDown = 30;
        }
    }
}
void p1won()
{
    gameStatus = P1WIN;
}
void p2won()
{
    gameStatus = P2WIN;
}
int main()
{

    setColliders();
    initStars();
    if (!zap.loadFromFile("audio/laserShoot.wav"))
    {
        return -1;
    }
    if (!t.loadFromFile("textures/outline.png"))
    {
        return -1;
    }

    window.setFramerateLimit(60);

    Collider c1(0, 0, 10, 32);
    Collider c2(0, 0, 10, 10);
    cout << c2.checkCollition(c1);
    bool lmbPressed = false;
    font.loadFromFile("fonts/PixelOperator.ttf");
    s.loadFromFile("textures/sun.png");
    font.setSmooth(false);
    
    while (window.isOpen())
    {
        cout<<gameStatus;
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (gameStatus == MAIN_MENU)
        {
            window.clear();
            sf::Text text;
            sf::Text otherText;
            sf::Sprite menuSun;

            menuSun.setTexture(s);
            menuSun.scale(8, 8);
            menuSun.setOrigin(3, 3);
            menuSun.setPosition(screenWidth / 2, screenWidth / 2);

            text.setFont(font);
            text.setString("spacewar!");
            text.setFillColor(sf::Color::White);
            text.scale(4, 4);
            text.setPosition(300, 200);

            otherText.setFont(font);
            otherText.setString("a recreation by vivithequeen\n        press enter to play");
            otherText.setFillColor(sf::Color::White);
            otherText.scale(2.5, 2.5);
            otherText.setPosition(120, 700);
            drawStars();

            window.draw(text);
            window.draw(menuSun);
            window.draw(otherText);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
            {
                // left key is pressed: move our character
                gameStatus = GAME;
            }
        }
        else if (gameStatus == GAME)
        {
            p1.teleportCoolDown -= 1;
            p1.laserCoolDown -= 1;
            p2.teleportCoolDown -= 1;
            p2.laserCoolDown -= 1;

            p1Inputs();
            p2Inputs();
            for (int i = 0; i < 360; i++)
            {
                if (colliders[i].collider.checkCollition(p1.collider) and p1.teleportCoolDown < 0)
                {
                    p1.setPosition(colliders[colliders[i].getOpposite()].x, colliders[colliders[i].getOpposite()].y);

                    p1.teleportCoolDown = 25;
                }
                if (colliders[i].collider.checkCollition(p2.collider) and p2.teleportCoolDown < 0)
                {
                    p2.setPosition(colliders[colliders[i].getOpposite()].x, colliders[colliders[i].getOpposite()].y);

                    p2.teleportCoolDown = 25;
                }
            }
            sf::Vector2f p1nv = sf::Vector2f(sun.x, sun.y) - sf::Vector2f(p1.x, p1.y);
            sf::Vector2f p2nv = sf::Vector2f(sun.x, sun.y) - sf::Vector2f(p2.x, p2.y);
            float p1nvl = getVectorLength(p1nv);
            float p2nvl = getVectorLength(p2nv);
            p1nv.x /= p1nvl / 2.0;
            p1nv.y /= p1nvl / 2.0;
            p2nv.x /= p2nvl / 2.0;
            p2nv.y /= p2nvl / 2.0;
            p1.addVelocity(p1nv);
            p2.addVelocity(p2nv);

            if (sun.checkCenterCollition(p1.x, p1.y))
            {

                p2won();
            }
            if (sun.checkCenterCollition(p2.x, p2.y))
            {
                p1won();
            }
            window.clear();

            sf::RectangleShape r(sf::Vector2f(screenWidth, screenWidth));
            r.setFillColor(sf::Color(13, 43, 69));
            window.draw(r);
            for (int i = 0; i < 1024; i++)
            {
                if (!lasers[i].isEmpty)
                {
                    if (lasers[i].update())
                    {
                        lasers[i] = Laser();
                    }
                    else
                    {
                        if (lasers[i].checkCollition(p1.x, p1.y))
                        {
                            cout << "yeah";
                            p2won();
                        }

                        else if (lasers[i].checkCollition(p2.x, p2.y))
                        {
                            p1won();
                        }
                        window.draw(lasers[i].getSprite());
                    }
                }
            }

            sf::Sprite outline(t);
            outline.scale(4, 4);
            drawStars();
            // window.draw(sun.debugDraw(p));

            p1.updatePosition();
            p2.updatePosition();
            window.draw(p1.getSprite());
            window.draw(p2.getSprite());
            window.draw(outline);
            window.draw(sun.getSprite());

            window.display();
        }
        else if (gameStatus == P1WIN)
        {
            window.clear();
            sf::Text text;

            text.setFont(font);
            text.setString("P1 WON!");
            text.setFillColor(sf::Color::White);
            text.scale(4, 4);
            text.setPosition(300, 200);

            drawStars();

            window.draw(text);

            window.display();
        }
        else if (gameStatus == P2WIN)
        {
            window.clear();
            sf::Text text;

            text.setFont(font);
            text.setString("P2 WON!");
            text.setFillColor(sf::Color::White);
            text.scale(4, 4);
            text.setPosition(300, 200);

            drawStars();

            window.draw(text);

            window.display();
        }
    }
}