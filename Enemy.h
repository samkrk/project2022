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

  Enemy(); // spawncoords default to (0,0)
  Enemy(sf::Vector2f origin); // sets spawnCoords to given origin

  void isShot(Player *player); // checks if shot by players bullets
  bool playerInRange(Player *player); // checks if distance to player is less than the targeting range
  void move(Player *player); // moves enemy based on tracking algorithim

  void print(); // displays purpose of enemy
};

#endif
