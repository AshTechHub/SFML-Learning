#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600),"SFML Tutorial - Survival Game");
    window.setFramerateLimit(60);
    cout<<"Window created!\n";

    sf::RectangleShape rect(sf::Vector2f(100.f,60.f));
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(350.f,270.f);

    sf::CircleShape circle(25.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(0.f,0.f);

    const float speed = 200.f;

    sf::Clock clock;

    while(window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        float dt = deltaTime.asSeconds();

        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                cout<<"Window closed!\n";
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    cout<<"Bang!\n";
                }
            }

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    cout<<"Window closed!\n";
                    window.close();
                }
            }

            if(event.type == sf::Event::MouseMoved)
            {
                circle.setPosition(event.mouseMove.x,event.mouseMove.y);
            }
        }

        sf::Vector2f movement(0.f,0.f);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            movement.y--;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            movement.y++;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            movement.x--;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            movement.x++;
        }

        float length = sqrt((movement.x * movement.x) + (movement.y * movement.y));

        if(length>0)
        {
            movement.x/=length;
            movement.y/=length;

            movement *= speed * dt;
        }

        rect.move(movement);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            rect.setFillColor(sf::Color::Magenta);
        }
        else
        {
            rect.setFillColor(sf::Color::Green);
        }

        window.clear(sf::Color::White);

        window.draw(rect);
        window.draw(circle);
        
        window.display();
    }
    return 0;
}