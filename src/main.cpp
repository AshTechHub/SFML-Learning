#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280,720),"SFML Tutorial - Survival Game");
    cout<<"Window Created!\n";

    sf::RectangleShape rect(sf::Vector2f(200.f,100.f));
    rect.setFillColor(sf::Color::Green);//540,310
    rect.setPosition(300.f,200.f);
    rect.move(240.f,110.f);

    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(590.f,240.f);//590,310
    circle.move(0.f,70.f);

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                cout<<"Window closed!\n";
                window.close();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            rect.move(0.f,-0.5f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            rect.move(-0.5f,0.f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            rect.move(0.f,0.5f);

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            rect.move(0.5f,0.f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            //window.clear(sf::Color::Black);
            rect.setFillColor(sf::Color::Magenta);
    
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            circle.move(0.f,-0.5f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            circle.move(-0.5f,0.f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            circle.move(0.f,0.5f);

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            circle.move(0.5f,0.f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            circle.setFillColor(sf::Color::Yellow);
        }

        window.clear(sf::Color::Blue);    
        
        window.draw(rect);
        window.draw(circle);


        window.display();

    }

    return 0;
}