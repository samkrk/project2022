#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main(){
    int height = 1600;
    int length = 2560;
    
    
    // create window
    sf::RenderWindow window(sf::VideoMode(length,height),"Window");

    // create texture of image and map onto sprite
    sf::Texture texture;
    if (!texture.loadFromFile("image.png",sf::IntRect(10, 10, length, height)))
    {
        cout << "texture failed to load" << endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // create shape
    sf::CircleShape player(60.f,4);
    player.setPosition(450.f, 400.f);
    sf::Vector2f position = player.getPosition();
    // get the bounding box of the entity
    sf::FloatRect boundingBox = player.getGlobalBounds();

    // main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::TextEntered:
                    
                    cout << static_cast<char>(event.text.unicode) << endl;
                    //player.move(10.f,10.f);
                break;
                case sf::Event::Closed:
                    window.close();
                break;
                default:
                break;
            } 
        }
        position = player.getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {if (position.x>0){player.move(-1.f, 0.f);}}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {if (position.x<(length-120)){player.move(1.f, 0.f);}}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {if (position.y>0){player.move(0.f, -1.f);}}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {if (position.y<(height-180)){player.move(0.f, 1.f);}}

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.draw(player);
        window.display();
    }
    return 0;
}