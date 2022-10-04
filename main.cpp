#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main(){
    // size of my screen  
    int height = 1600;
    int length = 2560;
    
    // timer
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("font.ttf")){
        return -1;
    }
    text.setFont(font);
    text.setPosition(length/2 , 0);
    sf::Time t1 = sf::seconds(0.5f);
    
    // create window
    // remove sf::Style::Fullscreen if it doesnt work
    sf::RenderWindow window(sf::VideoMode(length,height),"Window",sf::Style::Fullscreen);
    bool isFullscreen = true;

    // create texture of image and map onto sprite
    sf::Texture texture;
    if (!texture.loadFromFile("image.png",sf::IntRect(10, 10, length, height)))
    {
        cout << "texture failed to load" << endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    
    // create player
    sf::RectangleShape player(sf::Vector2f(60.f,100.f));
    player.setPosition((length/2), height/2+40);
    sf::Vector2f position = player.getPosition();
        // get the bounding box of the entity
        sf::FloatRect boundingBox = player.getGlobalBounds();
        // create velocity vector for player
        sf::Vector2f velocity = (sf::Vector2f(0,0));



    // create platform 
    sf::RectangleShape platform(sf::Vector2f(500,40));
    platform.setPosition(sf::Vector2f(length/2,height/2));

    // create ground 
    sf::RectangleShape ground(sf::Vector2f(length,5));
    ground.setPosition(sf::Vector2f(0,1500));


    // main game loop
    sf::Clock clock;
    sf::Time elapsed;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Return:
                            if (true == isFullscreen){
                                window.create(sf::VideoMode(length,height),"Window",sf::Style::Default);
                                isFullscreen = false;
                            }
                            else 
                            {
                                window.create(sf::VideoMode(length,height),"Window",sf::Style::Fullscreen);
                                isFullscreen = true;
                            }

                        break;
                        default:
                        break;
                    }
                break;
                case sf::Event::Closed:
                    window.close();
                break;
                default:
                break;
            } 
        }
        // movement of player
        position = player.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {if (position.x>0){player.move(-1.f, 0.f);}}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {if (position.x<(length-60)){player.move(1.f, 0.f);}}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {if (position.y>0){player.move(0.f, -1.f);}}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {if (position.y<(height-200)){player.move(0.f, 1.f);}}

        // gravity
        if (position.y<(height-200)){

        }

        elapsed += clock.restart();
        text.setString(to_string(elapsed.asSeconds()));

        // drawing everything 
        window.clear(sf::Color::Black); // clear window 
        window.draw(sprite);
        window.draw(player);
        window.draw(platform);
        window.draw(ground);
        window.draw(text);
        window.display(); // display 
    }
    return 0;
}