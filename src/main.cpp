#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280,720),"SFML Tutorial - Survival Game");
    cout<<"Window Created!\n";
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
        window.clear(sf::Color::Blue);

        sf::RectangleShape rect(sf::Vector2f(200.f,100.f));
        rect.setFillColor(sf::Color::Green);//540,310
        rect.setPosition(300.f,200.f);
        rect.move(240.f,110.f);

        sf::CircleShape circle(50.f);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(590.f,240.f);//590,310
        circle.move(0.f,70.f);

        sf::RectangleShape rect2(sf::Vector2f(450.f,50.f));
        rect2.setFillColor(sf::Color::Yellow);//415,260
        rect2.setPosition(300.f,120.f);
        rect2.move(115.f,140.f);

        sf::RectangleShape rect3(sf::Vector2f(450.f,50.f));
        rect3.setFillColor(sf::Color::Yellow);//415,410
        rect3.setPosition(700.f,560.f);
        rect3.move(-285.f,-150.f);
    
        
        window.draw(rect);
        window.draw(circle);
        window.draw(rect2);
        window.draw(rect3);

        window.display();

    }

    return 0;
}