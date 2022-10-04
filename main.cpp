#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
using namespace std;

int main(){
    // sf::RenderWindow window;
    // sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"Window",sf::Style::Fullscreen);
    window.create(sf::VideoMode(900, 900), "SFML Gravity", sf::Style::Titlebar | sf::Style::Close);
    // window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);

    //Player Object:
    Player player(sf::Vector2f(40,40));
    player.setPos(sf::Vector2f(50,700));


    //Gravity Variables:
    const int groundHeight = 700;
    const float gravitySpeed = 0.3;
    bool isJumping = false;

    //Main Loop:
    while (window.isOpen()) {
 
        sf::Event Event;
        const float moveSpeed = 0.2;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.move(sf::Vector2f(0,-moveSpeed));
            isJumping = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.move(sf::Vector2f(moveSpeed,0));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.move(sf::Vector2f(-moveSpeed,0));
        }

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
        }


        window.clear();
        player.drawTo(window);
        window.display();
        }
}