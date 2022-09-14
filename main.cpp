#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main(){
    int height = 3840;
    int length = 1080;
    
    // create window
    sf::RenderWindow window(sf::VideoMode(height,length),"Window");

    // create texture of image and map onto sprite
    sf::Texture texture;
    if (!texture.loadFromFile("image.png",sf::IntRect(10, 10, height, length)))
    {
        cout << "texture failed to load" << endl;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // create shape
    sf::CircleShape player(60.f,4);
    player.setPosition(450.f, 400.f);

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {player.move(-1.f, 0.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {player.move(1.f, 0.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {player.move(0.f, -1.f);}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {player.move(0.f, 1.f);}

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.draw(player);
        window.display();
    }
    return 0;
}