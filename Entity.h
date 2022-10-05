#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
 public:
  sf::RectangleShape body;
  sf::Vector2f size;
  int health;
  float speed;
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f acceleration;
  bool isAlive;

  Entity();

  void draw(sf::RenderWindow &window);

  void setPos(sf::Vector2f newPosition);
  void setVel(sf::Vector2f newVelocity);
  void setAcc(sf::Vector2f newAcceleration);
  void addPos(sf::Vector2f addPosition);  // increment position, current
                                          // position + change in position
  void addVel(sf::Vector2f addVelocity);
  void addAcc(sf::Vector2f addAcceleration);

  void update();
  //virtual void print() = 0; to make abtract, will do later
};

#endif