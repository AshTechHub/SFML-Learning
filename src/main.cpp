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
    float movementSpeed;
    bool loop;
};

enum class PlayerState
{
    idle, 
    walk,
    run,
    attack,
    hurt,
    death,
    jump,
    Count
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280,720),"SFML Tutorial - Survival Game");
    window.setFramerateLimit(60);
    cout<<"Window created!\n";

    sf::Texture idleTexture;
    if(!idleTexture.loadFromFile("assets/textures/Player/Swordsman/Idle_2.png"))
    {
        cout<<"Idle Texture failed to load!\n";
    }

    sf::Texture walkTexture;
    if(!walkTexture.loadFromFile("assets/textures/Player/Swordsman/Walk.png"))
    {
        cout<<"Walk Texture failed to load!\n";
    }

    sf::Texture runTexture;
    if(!runTexture.loadFromFile("assets/textures/Player/Swordsman/Run.png"))
    {
        cout<<"Run Texture failed to load!\n";
    }

    sf::Texture attackTexture;
    if(!attackTexture.loadFromFile("assets/textures/Player/Swordsman/Attack_2.png"))
    {
        cout<<"Attack Texture failed to load!\n";
    }

    sf::Texture hurtTexture;
    if(!hurtTexture.loadFromFile("assets/textures/Player/Swordsman/Hurt.png"))
    {
        cout<<"Hurt Texture failed to load!\n";
    }

    sf::Texture deathTexture;
    if(!deathTexture.loadFromFile("assets/textures/Player/Swordsman/Dead.png"))
    {
        cout<<"Dead Texture failed to load!\n";
    }

    sf::Texture jumpTexture;
    if(!jumpTexture.loadFromFile("assets/textures/Player/Swordsman/Jump.png"))
    {
        cout<<"Jump Texture failed to lead!\n";
    }

    sf::Sprite playerSprite;
    playerSprite.setTexture(idleTexture);

    playerSprite.setTextureRect(sf::IntRect(0,0,128,128));

    sf::FloatRect bounds = playerSprite.getLocalBounds();

    playerSprite.setOrigin(bounds.width/2.f,bounds.height/2.f);

    playerSprite.setScale(2.f,2.f);

    playerSprite.setPosition(200.f,590.f);

    playerSprite.setRotation(0.f);

    Animation idle;
    idle.texture = &idleTexture;
    idle.totalFrames = 3;
    idle.frameWidth = 128;
    idle.frameHeight = 128;
    idle.animationSpeed = 1.5f;
    idle.movementSpeed = 0.f;
    idle.loop = false;

    Animation walk;
    walk.texture = &walkTexture;
    walk.totalFrames = 8;
    walk.frameWidth = 128;
    walk.frameHeight = 128;
    walk.animationSpeed = 0.1f;
    walk.movementSpeed = 200.f;
    walk.loop = true;

    Animation run;
    run.texture = &runTexture;
    run.totalFrames = 8;
    run.frameWidth = 128;
    run.frameHeight = 128;
    run.animationSpeed = 0.08f;
    run.movementSpeed = 350.f;
    run.loop = true;

    Animation attack;
    attack.texture = &attackTexture;
    attack.totalFrames = 3;
    attack.frameWidth = 128;
    attack.frameHeight = 128;
    attack.animationSpeed = 0.1f;
    attack.movementSpeed = 0.f;
    attack.loop = false;

    Animation hurt;
    hurt.texture = &hurtTexture;
    hurt.totalFrames = 3;
    hurt.frameWidth = 128;
    hurt.frameHeight = 128;
    hurt.animationSpeed = 0.15f;
    hurt.movementSpeed = 0.f;
    hurt.loop = false;

    Animation death;
    death.texture = &deathTexture;
    death.totalFrames = 3;
    death.frameWidth = 128;
    death.frameHeight = 128;
    death.animationSpeed = 0.3f;
    death.movementSpeed = 0.f;
    death.loop = false;

    Animation jump;
    jump.texture = &jumpTexture;
    jump.totalFrames = 8;
    jump.frameWidth = 128;
    jump.frameHeight = 128;
    jump.animationSpeed = 0.08f;
    jump.movementSpeed = 350.f;
    jump.loop = false;


    Animation *currentAnimation = &idle;

    Animation *nextAnimation = &idle;

    bool animationFinished = false;

    int currentFrame = 0;

    float animationTimer = 0.f;

    PlayerState currentState = PlayerState::idle;

    PlayerState wantedState = PlayerState::idle;

    Animation *animations[(int)PlayerState::Count];

    animations[(int)PlayerState::idle] = &idle;
    animations[(int)PlayerState::walk] = &walk;
    animations[(int)PlayerState::run] = &run;
    animations[(int)PlayerState::attack] = &attack;
    animations[(int)PlayerState::hurt] = &hurt;
    animations[(int)PlayerState::death] = &death;
    animations[(int)PlayerState::jump] = &jump;

    bool attackPressedLastFrame = false;
    bool hurtPressedLastFrame = false;
    bool deathPressedLastFrame = false;
    bool jumpPressedLastFrame = false;


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
            movement/=length;
        }

        bool attackPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::J);

        bool hurtPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::H);

        bool deathPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::K);

        bool jumpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

        
        if((currentState == PlayerState::attack || currentState == PlayerState::hurt || currentState == PlayerState::death || currentState == PlayerState::jump) && !animationFinished)
        {

        }
        else
        {
            if(deathPressed && !deathPressedLastFrame)
            {
                wantedState = PlayerState::death;
            }
            else if(hurtPressed && !hurtPressedLastFrame)
            {
                wantedState = PlayerState::hurt;
            }
            else if(attackPressed && !attackPressedLastFrame)
            {
                wantedState=PlayerState::attack;
            }
            else if(jumpPressed && !jumpPressedLastFrame)
            {
                wantedState=PlayerState::jump;
            }
            else if(length>0 && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            {
                wantedState=PlayerState::run;
            }
            else if(length>0)
            {
                wantedState=PlayerState::walk;
            }
            else
            {
                wantedState=PlayerState::idle;
            }
        }

        bool canLeaveCurrentState = false;

        switch(currentState)
        {
            case PlayerState::idle:
            case PlayerState::walk:
            case PlayerState::run:
                canLeaveCurrentState = true;
                break;

            case PlayerState::attack:
            case PlayerState::hurt:
            case PlayerState::jump:
                canLeaveCurrentState = animationFinished; 
                break;

            case PlayerState::death:
                canLeaveCurrentState = false;
                break;
        }

        if(canLeaveCurrentState)
        {
            currentState = wantedState;
        }

        nextAnimation = animations[(int)currentState];

        if(nextAnimation != currentAnimation)
        {
            currentAnimation = nextAnimation;
            playerSprite.setTexture(*currentAnimation->texture);

            currentFrame = 0;

            animationTimer = 0;

            animationFinished = false;

            playerSprite.setTextureRect(sf::IntRect(0,0,currentAnimation->frameWidth,currentAnimation->frameHeight));
        }

        animationTimer += dt;

        if(animationTimer > currentAnimation->animationSpeed)
        {
            if(currentAnimation == &idle)
            {
                playerSprite.setTextureRect(sf::IntRect(0,0,128,128));
            }
            else
            {         
                currentFrame++;

                if(currentFrame >= currentAnimation->totalFrames)
                {
                    if(currentAnimation->loop)
                    {
                        currentFrame = 0;
                    }
                    else
                    {
                        currentFrame = currentAnimation->totalFrames - 1;
                        animationFinished = true;
                    }
                }

                playerSprite.setTextureRect(sf::IntRect(currentFrame * currentAnimation->frameWidth, 0, currentAnimation->frameWidth, currentAnimation->frameHeight));
            }

            animationTimer = 0;
        }

        movement *= currentAnimation->movementSpeed * dt;

        playerSprite.move(movement);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            playerSprite.rotate(-100.f * dt);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            playerSprite.rotate(100.f * dt);
        }

        attackPressedLastFrame = attackPressed;
        hurtPressedLastFrame = hurtPressed;
        deathPressedLastFrame = deathPressed;
        jumpPressedLastFrame = jumpPressed;

        window.clear(sf::Color(45,52,71));

        window.draw(playerSprite);
        
        window.display();
    }

    return 0;
}
