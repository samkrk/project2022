#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include "Object.h"
class Entity : public Object {
 public:
  int health;
  float speed;
  sf::Vector2f ofScreenPos;
  sf::Vector2f zeroVec;
  sf::Vector2f velocity;
  sf::Vector2f acceleration;
  bool isAlive;
  bool onPlatform;
  bool onGround;
  bool onLWall;
  bool onRWall;

  Entity();
  
  void setPos(sf::Vector2f newPosition);
  void setVel(sf::Vector2f newVelocity);
  void setAcc(sf::Vector2f newAcceleration);
  void addPos(sf::Vector2f addPosition);  // increment position, current
                                          // position + change in position
  void addVel(sf::Vector2f addVelocity);
  void addAcc(sf::Vector2f addAcceleration);
  //virtual void print() = 0; to make abtract, will do later
};

#endif