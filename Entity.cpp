#include "Entity.h"
#include <SFML/Graphics.hpp>

Entity::Entity() {
  size = sf::Vector2f(50,50);
  body.setSize(size);
  fillColor = sf::Color::Magenta;
  body.setFillColor(fillColor);

  speed = 2;
  onPlatform = false;
  onGround = false;
  onLWall = false;
  onRWall = false;

  ofScreenPos = sf::Vector2f(-100, -100);
  zeroVec = sf::Vector2f(0, 0);

  position = zeroVec;
  velocity = zeroVec;
  acceleration = zeroVec;

  isAlive = true;
}

void Entity::setPos(sf::Vector2f newPosition) {this->position = newPosition;}
void Entity::setVel(sf::Vector2f newVelocity) { this->velocity  = newVelocity; }
void Entity::setAcc(sf::Vector2f newAcceleration) {
  this->acceleration = newAcceleration;
}
void Entity::addPos(sf::Vector2f addPosition) {this->position += addPosition;}
void Entity::addVel(sf::Vector2f addVelocity) {this->velocity += addVelocity; }
void Entity::addAcc(sf::Vector2f addAcceleration) {this->acceleration += addAcceleration; }
