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
    sf::Text *highScores;


    bool playSelected;
    bool leaderboardSelected;

    bool isSelect;


    void highlightingWords();

    void isSelected();

    void displayMenu(sf::RenderWindow *win);

    void displayLeaderBoard(sf::RenderWindow *win, int Highscore);

    void displayHowToPlay(sf::RenderWindow *win);

    void displayWinScreen(sf::RenderWindow *win, int gameTime, int prevRecord);

};


#endif