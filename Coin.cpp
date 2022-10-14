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
}

void Coin::playerCollect(Player *player) {
  if (collision(player))
  {
    isCollected = true;
    position = ofScreenPos;
    update();
  }
}