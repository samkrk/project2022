#include <SFML/Graphics.hpp>

#include "Object.h"

Object::Object() {
  size = sf::Vector2f(50, 50);
  body.setSize(size);
  fillColor = sf::Color::Magenta;
  body.setFillColor(fillColor);
  position = sf::Vector2f(200,200);
}

bool Object::collision(Object *object){
  // check bounding box -> then check which side the entity is touching
  bool belowTop = false;
  bool aboveBottom = false;
  bool rightOfSide = false;
  bool leftOfSide = false;
  // top
  if (object->position.y > this->position.y - object->size.y) {
    belowTop = true;
  }
  // bottom
  if (object->position.y < this->position.y + this->size.y) {
    aboveBottom = true;
  }
  // left
  if (object->position.x > this->position.x - object->size.x) {
    rightOfSide = true;
  }
  // right
  if (object->position.x < this->position.x + this->size.x) {
    leftOfSide = true;
  }
  return (belowTop && aboveBottom && rightOfSide && leftOfSide);
}

void Object::draw(sf::RenderWindow &window) { window.draw(body); }

void Object::update() { this->body.setPosition(this->position); }