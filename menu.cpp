#include "menu.h"

Menu::Menu(){
  win.create(sf::VideoMode(1800, 1500), "Menu"); // create window
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
  

  options.setOutlineColor(sf::Color::White);
  options.setFont(font);
  options.setFillColor(sf::Color::White);
  options.setPosition(300,800);
  options.setString("Options");
  options.setCharacterSize(75);


  playSelected = true;
}

void Menu::isSelected(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if (playSelected){
                win.close();
            }
        }
}

void Menu::highlightingWords(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            playSelected = false;
        }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            playSelected = true;
        }
    if (playSelected){
        play.setFillColor(sf::Color::Red);
        play.setCharacterSize(100);
        options.setFillColor(sf::Color::White);
        options.setCharacterSize(75);
    }
    else{
        options.setFillColor(sf::Color::Red);
        options.setCharacterSize(100);
        play.setFillColor(sf::Color::White);
        play.setCharacterSize(75);
    }
}

void Menu::run(){
    // game loop
    while (win.isOpen()) {
    sf::Event event;
    while (win.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        win.close();
      }
    }
    
    highlightingWords();
    isSelected();
        
    win.clear();
    win.draw(bg);
    win.draw(play);
    win.draw(options);
    win.display();
    }
    
}