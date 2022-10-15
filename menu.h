#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu{
    public:
    Menu();
    sf::RenderWindow win;
    sf::Font font;
    sf::Text play;
    sf::Text options;
    sf::Texture background;
    sf::Sprite bg;


    bool playSelected;

    void highlightingWords();

    void isSelected();

    void run();




};


#endif