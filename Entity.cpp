#include "Entity.h"
#include <SFML/Graphics.hpp>

Entity::Entity() {
  size = sf::Vector2f(50,50);
  body.setSize(size);
  body.setFillColor(sf::Color::Magenta);

  speed = 2;
  onPlatform = false;

  position = sf::Vector2f(0, 0);
  velocity = sf::Vector2f(0,0);
  acceleration = sf::Vector2f(0, 0);
}

void Entity::draw(sf::RenderWindow &window) { window.draw(body); }

void Entity::setPos(sf::Vector2f newPosition) {this->position = newPosition;}
void Entity::setVel(sf::Vector2f newVelocity) { this->velocity  = newVelocity; }
void Entity::setAcc(sf::Vector2f newAcceleration) {
  this->acceleration = newAcceleration;
}
void Entity::addPos(sf::Vector2f addPosition) {this->position += addPosition;}
void Entity::addVel(sf::Vector2f addVelocity) {this->velocity += addVelocity; }
void Entity::addAcc(sf::Vector2f addAcceleration) {this->acceleration += addAcceleration; }

void Entity::update() {
  this->body.setPosition(this->position);
}