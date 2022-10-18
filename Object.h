#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object {
 public:
  sf::RectangleShape body;
  sf::Color fillColor;
  sf::Vector2f size;
  sf::Vector2f position;

  Object();

  bool collision(Object *object);

  void draw(sf::RenderWindow &window);

  void update();
  // virtual void print() = 0; to make abtract, will do later
};

#endif