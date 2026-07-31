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
        rect.setFillColor(sf::Color::Green);

        window.draw(rect);

        window.display();

    }

    return 0;
}