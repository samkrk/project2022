#include <SFML/Graphics.hpp>
#include <iostream>

class Player{
public:
    sf::RectangleShape player;

    Player(sf::Vector2f size);

    void drawTo(sf::RenderWindow &window);

    void move(sf::Vector2f distance);

    void setPos(sf::Vector2f newPos);

    float getY();
    float getX();

private:
    
};
