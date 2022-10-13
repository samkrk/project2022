#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Player.h"

class Enemy : public Entity {
 public:
  int targetingRange;
  float trackingSpeed;

  sf::Vector2f spawnCoords;

  Enemy();
  Enemy(sf::Vector2f origin);
  bool playerInRange(Player *player);
  void move(Player *player);
};

#endif