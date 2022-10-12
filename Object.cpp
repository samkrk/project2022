#include <SFML/Graphics.hpp>

#include "Object.h"

Object::Object() {
  size = sf::Vector2f(50, 50);
  body.setSize(size);
  fillColor = sf::Color::Magenta;
  body.setFillColor(fillColor);
  position = sf::Vector2f(200,200);
}

void Object::draw(sf::RenderWindow &window) { window.draw(body); }

void Object::update() { this->body.setPosition(this->position); }