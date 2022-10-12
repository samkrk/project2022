#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

Player::Player() {
  this->magSize = 20;
  this->bulletIndex = 0;
  bullets = new Bullet[magSize];

  time.asMilliseconds();
  this->fireRate = 100;
  this->relaodTime = 1000;

  this->reloading = false;
}

void Player::shoot(int direction) {
  if (bulletIndex == magSize)
  {
    std::cout << "Out of ammo" << std::endl;
    return;
  }
  bullets[bulletIndex].setPos(this->position);
  bullets[bulletIndex].setVel(sf::Vector2f(bullets->speed*direction,0));
  bulletIndex++;
  std::cout << "Bullet " << bulletIndex << " of " << magSize << std::endl;
  clock.restart();
}

void Player::reload() {
  reloading = true;
  if (timeSinceShot > relaodTime)
  {
    reloading = false;
    bulletIndex = 0;
    for (int i = 0; i < magSize; i++)
    {
      bullets[i].setVel(zeroVec);
      bullets[i].setPos(ofScreenPos);
    }
  }
}