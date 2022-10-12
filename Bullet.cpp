#include "Bullet.h"

Bullet::Bullet() {
  this->isFired = false;
  this->position = sf::Vector2f(-100,-100);
  this->size = sf::Vector2f(20,10);
  this->body.setSize(size);
  this->fillColor = sf::Color::Red;
  this->body.setFillColor(fillColor);
  this->speed = 20;
}

Bullet::Bullet(float speed) {
  Bullet();
  this->speed = speed;
}

