#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

class Object {
 public:
  sf::RectangleShape body;
  sf::Color fillColor;
  sf::Vector2f size;
  sf::Vector2f position;

  Object(); // initialises abject

  bool collision(Object *object); // checks for collision with anotehr object

  void draw(sf::RenderWindow &window);  // draws object to renderwindow

  void update(); // sets the position of the body based on its member variables
  
  virtual void print() = 0; // will be implemented in derived classes to print important info
};

#endif