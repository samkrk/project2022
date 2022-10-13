#include "Enemy.h"

#include <math.h>

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

Enemy::Enemy() { Enemy(sf::Vector2f(0, 0)); }

Enemy::Enemy(sf::Vector2f origin) {
  this->spawnCoords = origin;
  this->size = sf::Vector2f(30, 30);
  body.setSize(this->size);
  this->position = origin;
  this->fillColor = sf::Color::Cyan;
  this->body.setFillColor(fillColor);
  this->setVel(sf::Vector2f(-1, -1));
  this->setAcc(sf::Vector2f(0, 1));

  this->targetingRange = 350;
  this->trackingSpeed = 0.05;
}
bool Enemy::playerInRange(Player *player) {
  sf::Vector2f direction = player->position - this->position;
  float distance = pow(direction.x, 2) + pow(direction.y, 2);
  if (distance < targetingRange * targetingRange) {
    return true;
  }
  return false;
}
void Enemy::move(Player *player) {
  sf::Vector2f direction;
  if (!playerInRange(player)) {
    direction.x = this->spawnCoords.x - this->position.x;
    setVel(sf::Vector2f(0.1*trackingSpeed*direction.x, velocity.y));
  } else {
    direction = player->position - this->position;
    this->setVel(trackingSpeed * direction);
  }
  setAcc(sf::Vector2f(0,2));
}