#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600),"SFML Tutorial - Survival Game");
    cout<<"Window created!\n";

    sf::RectangleShape rect(sf::Vector2f(200,100));
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(300.f,250.f);

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(0.f,0.f);

    const float speed = 0.5f;

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    cout<<"Bang!\n";
                }
            }
            if(event.type == sf::Event::MouseMoved)//&& event.mouseButton.button == sf::Mouse::Left
            {
                cout<<"Mouse: "<<event.mouseMove.x<<","<<event.mouseMove.y<<"\n";
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            rect.move(0.f,-speed);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            rect.move(0.f,speed);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            rect.move(-speed,0.f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            rect.move(speed,0.f);
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            rect.setFillColor(sf::Color::Magenta);
        }
        else
        {
            rect.setFillColor(sf::Color::Green);
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
        {
            circle.setFillColor(sf::Color::Yellow);
        }
        else
        {
            circle.setFillColor(sf::Color::Red);
        }

        // sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // cout << mousePos.x << " " << mousePos.y << endl;

        //sf::Vector2i rectPos = rect.getPosition(window)
        //DON't know how to change background color by storing it in a variable
        //Don't know how to compare the positions of 2 shapes to know when they collide

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {   cout<<"Window collapsed!\n";
            window.close();
        }

        window.clear(sf::Color::Blue);

        window.draw(rect);
        window.draw(circle);

        window.display();
    }

    return 0;
}