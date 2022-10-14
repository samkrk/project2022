#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Bullet.h"
#include <iostream>

class Player : public Entity {
 public:
 int magSize;
 int bulletIndex;
 Bullet *bullets;

 sf::Clock clock;
 sf::Time time;
 float timeSinceShot;
 int fireRate; // in milliseconds
 int relaodTime; // in milliseconds
 bool reloading;

 Player();
 void shoot(int direction);
 void reload();

 void isKilled(Entity *enemy);
 void respawn();
};

#endif