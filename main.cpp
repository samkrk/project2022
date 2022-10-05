#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
using namespace std;

int main(){
<<<<<<< HEAD
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
    sf::RenderWindow window(sf::VideoMode(length,height),"Window");
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
    float a = 0.0001;
    float v = 0;
    sf::Vector2f position = player.getPosition();
        // get the bounding box of the entity
        sf::FloatRect boundingBox = player.getGlobalBounds();
        // create velocity vector for player
        sf::Vector2f velocity = (sf::Vector2f(0,0));



    // create platform 
    sf::RectangleShape platform(sf::Vector2f(500,40));
    platform.setPosition(sf::Vector2f(length/2,height/2));
=======
    // sf::RenderWindow window;
    // sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"Window",sf::Style::Fullscreen);
    window.create(sf::VideoMode(900, 900), "SFML Gravity", sf::Style::Titlebar | sf::Style::Close);
    // window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);
>>>>>>> 7aaa11ee813583f48de9ce13c34eba400e52e954

    //Player Object:
    Player player(sf::Vector2f(40,40));
    player.setPos(sf::Vector2f(50,700));


<<<<<<< HEAD
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
=======
    //Gravity Variables:
    const int groundHeight = 700;
    const float gravitySpeed = 0.3;
    bool isJumping = false;
>>>>>>> 7aaa11ee813583f48de9ce13c34eba400e52e954

    //Main Loop:
    while (window.isOpen()) {
 
        sf::Event Event;
        const float moveSpeed = 0.1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.move(sf::Vector2f(0,-moveSpeed));
            isJumping = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move(sf::Vector2f(moveSpeed,0));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move(sf::Vector2f(-moveSpeed,0));
        }
<<<<<<< HEAD
        // movement of player
        position = player.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {if (position.x>0){player.move(-1.f, 0.f);}}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {if (position.x<(length-60)){player.move(1.f, 0.f);}}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {if (position.y>0){v = -1;}}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {if (position.y<(height-200)){v = 1;}}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
              sf::Keyboard::isKeyPressed(sf::Keyboard::Down) {
            player.move(0.f, v);
          }
        // gravity
        if (position.y<(height-200)){
          v += a;
          player.move(0.f, v);
=======

        //Event Loop:
        while (window.pollEvent(Event)) {
            switch (Event.type) {
 
            case sf::Event::Closed:
                window.close();
 
            case sf::Event::KeyReleased:
                isJumping = false;
            default:;
            }
        }

        
        //Gravity Logic:
        if (player.getY() < groundHeight && isJumping == false) {
            player.move(sf::Vector2f(0,gravitySpeed));
>>>>>>> 7aaa11ee813583f48de9ce13c34eba400e52e954
        }


        window.clear();
        player.drawTo(window);
        window.display();
        }
}