#include <SFML/Graphics.hpp>
#include <iostream>

#include "Spring.h"

Spring::Spring() { Spring(this->size, this->position); }

Spring::Spring(sf::Vector2f size, sf::Vector2f origin) {
  fillColor = sf::Color::Yellow;
  this->body.setFillColor(fillColor);
  this->damping = 10;

  this->size = size;
  this->position = origin;
  body.setSize(this->size);
  body.setPosition(this->position);
  std::cout << this->damping << std::endl;
}