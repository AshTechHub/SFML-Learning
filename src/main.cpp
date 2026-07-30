#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1915,600),"SFML Tutorial - Survival Game");
    cout<<"Window created!";
    while(window.isOpen())
    {
        
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                cout<<"\nWindow close requested.";
                window.close();
            } 

            if(event.type==sf::Event::KeyPressed)
                cout<<"\nA key was pressed.";

            if(event.type==sf::Event::MouseMoved)
                cout<<"\nMouse moved.";

            if(event.type==sf::Event::MouseButtonPressed)
                cout<<"\nMouse button pressed.";

           
        }
    }
    cout<<"Window collapsed!";

    window.clear();
    window.display();

    return 0;
}