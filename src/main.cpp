#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

struct Animation
{
    sf::Texture *texture;
    int totalFrames;
    int frameWidth;
    int frameHeight;
    float animationSpeed;
    bool loop;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280,720),"SFML Tutorial - Survival Game");
    window.setFramerateLimit(60);
    cout<<"Window created!\n";

    sf::Texture idleTexture;
    if(!idleTexture.loadFromFile("assets/textures/Player/Idle_2.png"))
    {
        cout<<"Walking Texture failed to load!\n";
    }
    else
    {
        cout<<"Walking Texture loaded successfully!\n";
    }

    sf::Texture walkTexture;
    if(!walkTexture.loadFromFile("assets/textures/Player/Walk.png"))
    {
        cout<<"Idle Texture failed to load!\n";
    }
    else
    {
        cout<<"Idle Texture loaded successfully!\n";
    }

    Animation idle;
    idle.texture = &idleTexture;
    idle.totalFrames = 3;
    idle.frameWidth = 128;
    idle.frameHeight = 128;
    idle.animationSpeed = 1.5f;
    idle.loop = true;

    Animation walk;
    walk.texture = &walkTexture;
    walk.totalFrames = 8;
    walk.frameWidth = 128;
    walk.frameHeight = 128;
    walk.animationSpeed = 0.1f;
    walk.loop = true;

    Animation *currentAnimation = &idle;

    Animation *nextAnimation = &idle;

    bool animationFinished = false;

    int currentFrame = 0;

    float animationTimer = 0.f;

    sf::Sprite playerSprite;
    playerSprite.setTexture(idleTexture);

    playerSprite.setTextureRect(sf::IntRect(0,0,128,128));

    sf::FloatRect bounds = playerSprite.getLocalBounds();

    playerSprite.setOrigin(bounds.width/2.f,bounds.height/2.f);

    playerSprite.setScale(1.5f,1.5f);

    playerSprite.setPosition(400.f,624.f);

    playerSprite.setRotation(0.f);

    
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

            nextAnimation = &walk;
        }
        else
        {
            nextAnimation = &idle;
        }

        if(nextAnimation != currentAnimation)
        {
            currentAnimation = nextAnimation;
            playerSprite.setTexture(*currentAnimation->texture);

            currentFrame = 0;

            animationTimer = 0;

            playerSprite.setTextureRect(sf::IntRect(0,0,currentAnimation->frameWidth,currentAnimation->frameHeight));
        }

        animationTimer += dt;

        if(animationTimer > currentAnimation->animationSpeed)
        {
            if(currentAnimation == &idle)
            {
                playerSprite.setTextureRect(sf::IntRect((currentAnimation->totalFrames-1) * currentAnimation->frameWidth, 0, currentAnimation->frameWidth, currentAnimation->frameHeight));
            }
            else
            {
                currentFrame = (currentFrame + 1) % currentAnimation->totalFrames;

                playerSprite.setTextureRect(sf::IntRect(currentFrame * currentAnimation->frameWidth, 0, currentAnimation->frameWidth, currentAnimation->frameHeight));
            }
            animationTimer = 0;
        }

        playerSprite.move(movement);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            playerSprite.rotate(-100.f * dt);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            playerSprite.rotate(100.f * dt);
        }

        window.clear(sf::Color::Yellow);

        window.draw(playerSprite);
        
        window.display();
    }
    return 0;
}