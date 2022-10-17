#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu{
    public:
    Menu();

    sf::Font font;
    sf::Text play;
    sf::Text leaderboard;
    sf::Texture background;
    sf::Sprite bg;

    sf::Text howToPlay[5];


    bool playSelected;
    bool leaderboardSelected;

    bool isSelect;


    void highlightingWords();

    void isSelected();

    void displayMenu(sf::RenderWindow *win);

    void displayHowToPlay(sf::RenderWindow *win);

};


#endif