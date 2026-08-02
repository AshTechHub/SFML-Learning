#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280,720),"SFML Tutorial - Survival Game");
    window.setFramerateLimit(60);
    cout<<"Window created!\n";

    sf::Texture playerIdleTexture;
    if(!playerIdleTexture.loadFromFile("assets/textures/Player/Idle_2.png"))
    {
        cout<<"Walking Texture failed to load!\n";
    }
    else
    {
        cout<<"Walking Texture loaded successfully!\n";
    }

    // sf::Texture playerTexture2;
    // playerTexture2.loadFromFile("assets/textures/adventurer_walk2.png");
    
    sf::Texture playerWalkTexture;
    if(!playerWalkTexture.loadFromFile("assets/textures/Player/Walk.png"))
    {
        cout<<"Idle Texture failed to load!\n";
    }
    else
    {
        cout<<"Idle Texture loaded successfully!\n";
    }

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerIdleTexture);

    playerSprite.setTextureRect(sf::IntRect(0,0,128,128));

    sf::FloatRect bounds = playerSprite.getLocalBounds();

    playerSprite.setOrigin(bounds.width/2.f,bounds.height/2.f);

    playerSprite.setScale(1.5f,1.5f);

    playerSprite.setPosition(400.f,624.f);

    playerSprite.setRotation(0.f);

    // cout << playerTexture.getSize().x << " "
    // << playerTexture.getSize().y << std::endl;
    //{TO PRINT THE SIZES}

    const int frameWidth = 128;

    const int frameHeight = 128;

    const int walkFrames = 8;

    const int idleFrames = 3;

    int currentFrame = 0;

    float animationTimer = 0.f;

    //bool firstFrame = true;

    const float speed = 200.f;

    bool isWalking = false;

    bool wasWalking = false;

    sf::Clock clock;

    while(window.isOpen())
    {
        sf::Time deltaTime = clock.restart();

        float dt = deltaTime.asSeconds();

        //playerSprite.rotate(1.f);  
        //{WORKS LIKE MOVE, ROTATES THE SPECIFIED ANGLE FROM THE CURRENT ANGLE}

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
            isWalking = true;
            movement.x/=length;
            movement.y/=length;

            movement *= speed * dt;
        }
        else
        {
            isWalking = false;
        }

        if(isWalking != wasWalking)
        {
            if(isWalking)
            {
                playerSprite.setTexture(playerWalkTexture);
            }
            else
            {
                playerSprite.setTexture(playerIdleTexture);
            }

            animationTimer = 0.f;

            currentFrame = 0;

            playerSprite.setTextureRect(sf::IntRect(0,0,frameWidth,frameHeight));
        }
        
        if(isWalking)
        {
            animationTimer += dt;

            if(animationTimer > 0.1f)
            {
                currentFrame = (currentFrame + 1) % walkFrames;

                playerSprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));

                animationTimer = 0;
            }
        }
        else
        {
            animationTimer += dt;

            if(animationTimer > 1.5f)
            {
                //currentFrame = (currentFrame + 1) % idleFrames;

                //playerSprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));

                playerSprite.setTextureRect(sf::IntRect((idleFrames - 1) * frameWidth,0,frameWidth, frameHeight));

                animationTimer = 0;
            }
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

        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        // {
        //     playerSprite.setTextureRect(sf::IntRect(0,80,80,110));
        // }
                                    //{WALKING MOVEMENT USING KEYS}

        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        // {
        //     playerSprite.setTextureRect(sf::IntRect(80,80,80,110));
        // }

        

        // if(animationTimer>=0.2f)
        // {
        //     if(firstFrame)
        //     {
        //         playerSprite.setTexture(playerTexture2);
        //     }
        //     else                 {USED FOR 2 DIFFERENT TEXTURES NOT FOR SPRITESHEET}
        //     {                                        
        //         playerSprite.setTexture(playerTexture);
        //     }

        //     firstFrame = !firstFrame;        

        //     animationTimer = 0.f;
            
        // }

        // if(animationTimer >= 0.1f)
        // {
        //     currentFrame++;

        //     if(currentFrame>=totalFrames)
        //     {
        //         currentFrame=0;
        //     }
                                            //{ONLY FOR ROOKIES}
        //     if(currentFrame == 0)
        //     {
        //         playerSprite.setTextureRect(sf::IntRect(0,0,128,128));
        //     }
        //     if(currentFrame == 1)
        //     {
        //         playerSprite.setTextureRect(sf::IntRect(128,0,128,128));
        //     }
        //     if(currentFrame == 2)
        //     {
        //         playerSprite.setTextureRect(sf::IntRect(256,0,128,128));
        //     }
        //     if(currentFrame == 3)
        //     {
        //         playerSprite.setTextureRect(sf::IntRect(384,0,128,128));
        //     }
        //     if(currentFrame == 4)
        //     {
        //         playerSprite.setTextureRect(sf::IntRect(512,0,128,128));
        //     }
        //     if(currentFrame == 5)
        //     {
        //         playerSprite.setTextureRect(sf::IntRect(640,0,128,128));
        //     }
        //     if(currentFrame == 6)
        //     {
        //         playerSprite.setTextureRect(sf::IntRect(768,0,128,128));
        //     }
        //     if(currentFrame == 7)
        //     {
        //         playerSprite.setTextureRect(sf::IntRect(896,0,128,128));
        //     }
        //     animationTimer=0;
            
        // }

        // if(animationTimer>=0.1f)
        // {
        //     // // currentFrame++;

        //    // // if(currentFrame>=totalFrames)
        //    // // {                                {ONLY FOR ROOKIES}
        //    // //     currentFrame=0;
        //    // // }

        //     currentFrame = (currentFrame + 1) % 8;

        //     playerSprite.setTextureRect(sf::IntRect(currentFrame * frameWidth,0,frameWidth,frameHeight));

        //     animationTimer=0;
        // }
        wasWalking = isWalking;

        window.clear(sf::Color::Yellow);

        window.draw(playerSprite);
        
        window.display();
    }
    return 0;
}