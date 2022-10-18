#include <SFML/Graphics.hpp>

#include "Coin.h"

Coin::Coin() {
  Coin(sf::Vector2f(500,500));
}

Coin::Coin(sf::Vector2f origin) {
  isCollected = false;
  size = sf::Vector2f(30, 30);
  body.setSize(size);
  fillColor = sf::Color(236,215,73);
  body.setFillColor(fillColor);
  
  position = origin;
  update();
  /*
  if (!skin.loadFromFile("coin.jpeg")){
    std::cout << "FAILED" << std::endl;
  }
  body.setFillColor(sf::Color::White);
  body.setTexture(&skin);
  */
}

void Coin::playerCollect(Player *player) {
  if (collision(player))
  {
    isCollected = true;
    position = ofScreenPos;
    update();
  }
}

void Coin::print() {
  std::cout << "Coins can be collected by a player" << std::endl;
}