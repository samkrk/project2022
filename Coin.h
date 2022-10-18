#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Player.h"

class Coin : public Entity {
 public:
  bool isCollected;

  Coin();
  Coin(sf::Vector2f origin);
  void playerCollect(Player *player);
};

#endif