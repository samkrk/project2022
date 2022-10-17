#include "Menu.h"
#include <string>

Menu::Menu(){
  font.loadFromFile("arcadefont.TTF");        // load font
  background.loadFromFile("background.jpeg"); // load background image

  bg.setTexture(background);
  bg.setScale(5,4.2);

  play.setOutlineColor(sf::Color::White);
  play.setFont(font);
  play.setFillColor(sf::Color::White);
  play.setPosition(300,500);
  play.setString("Play");
  play.setCharacterSize(75);
  

  leaderboard.setOutlineColor(sf::Color::White);
  leaderboard.setFont(font);
  leaderboard.setFillColor(sf::Color::White);
  leaderboard.setPosition(300,800);
  leaderboard.setString("Leaderboard");
  leaderboard.setCharacterSize(75);

  std::string intructions[5];
  intructions[0] = "Collect all the coins in each level to progress to the next";
  intructions[1] = "Watch out for pesky enemies as they will kill you!";
  intructions[2] = "Try and beat your high score by completeing the game as fast as you can!";
  intructions[3] = "\nUse wasd to move space to jump and your mouse to shoot";
  intructions[4] = "\nPress SPACE to start the game";

  for (int i = 0; i < 5; i++) {
    howToPlay[i].setOutlineColor(sf::Color::White);
    howToPlay[i].setFont(font);
    howToPlay[i].setFillColor(sf::Color::White);
    howToPlay[i].setPosition(300,600+50*i);
    howToPlay[i].setString(intructions[i]);
    howToPlay[i].setCharacterSize(40);
  }


  playSelected = true;
  leaderboardSelected = false;
  isSelect = false;
}

void Menu::isSelected(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                isSelect = true;
        }
}

void Menu::highlightingWords(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            playSelected = false;
            leaderboardSelected = true;
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            playSelected = true;
            leaderboardSelected = false;
        }
    if (playSelected){
        play.setFillColor(sf::Color::Red);
        play.setCharacterSize(100);
        leaderboard.setFillColor(sf::Color::White);
        leaderboard.setCharacterSize(75);
    }
    if (leaderboardSelected) {
      leaderboard.setFillColor(sf::Color::Red);
      leaderboard.setCharacterSize(100);
      play.setFillColor(sf::Color::White);
      play.setCharacterSize(75);
    }
}

void Menu::displayMenu(sf::RenderWindow *win){
    // game loop
    while (win->isOpen() && !isSelect) {
    sf::Event event;
    while (win->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        win->close();
      }
    }
    
    highlightingWords();
    isSelected();
        
    win->clear();
    win->draw(bg);
    win->draw(play);
    win->draw(leaderboard);
    win->display();
    }
    
}

void Menu::displayHowToPlay(sf::RenderWindow *win) {
  while (win->isOpen()) {
    sf::Event event;
    while (win->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        win->close();
      }
    }
    win->clear();
    win->draw(bg);
    for (int i = 0; i < 5; i++) {
      win->draw(howToPlay[i]);
    }
    win->display();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      break;
    }
    }
}