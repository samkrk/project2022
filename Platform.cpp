#include "Platform.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Platform::Platform() { Platform(this->size, this->position); }

Platform::Platform(sf::Vector2f size, sf::Vector2f origin) {
  fillColor = sf::Color::White;
  this->body.setFillColor(fillColor);
  this->damping = 0.6;

  this->size = size;
  this->position = origin;
  body.setSize(this->size);
  body.setPosition(this->position);
  std::cout << this->damping << std::endl;
}

void Platform::collisionPhysics(Entity *entity) {
  // only call if the collision function is true
  if (!collision(entity)) {
    return;
  }

  // update if player on platform
  if (entity->position.y + entity->size.y > this->position.y - 0.05 &&
      entity->position.y + entity->size.y < this->position.y + 0.05) {
    entity->onPlatform = true;
    entity->onGround = true;
  } else if (entity->position.x + entity->size.x > this->position.x - 0.5 &&
             entity->position.x + entity->size.x < this->position.x + 0.5) {
    entity->onPlatform = true;
    entity->onRWall = true;
  } else if (entity->position.x < this->position.x + this->size.x + 0.5 &&
             entity->position.x > this->position.x + this->size.x - 0.5) {
    entity->onPlatform = true;
    entity->onLWall = true;
  }

  // top
  //  bottom of entity below top of platform bounce up
  if (entity->position.y + entity->size.y > this->position.y &&
      entity->position.y + entity->size.y < this->position.y + 2) {
    entity->setPos(
        sf::Vector2f(entity->position.x, this->position.y - entity->size.y));
    if (!entity->onPlatform) {
      entity->setVel(damping *
                     sf::Vector2f(entity->velocity.x, -entity->velocity.y));
    }
  }
  // bottom
  //  top of entity above bottom of platform bounce down
  else if (entity->position.y < this->position.y + this->size.y &&
           entity->position.y > this->position.y + this->size.y - 2) {
    entity->setVel(damping *
                   sf::Vector2f(entity->velocity.x, -entity->velocity.y));
    entity->setPos(
        sf::Vector2f(entity->position.x, this->position.y + this->size.y));
  }
  // right
  //  left of entity left of right of platform
  else if (entity->position.x < this->position.x + this->size.x &&
           entity->position.x > this->position.x + this->size.x - 2) {
    entity->setVel(damping *
                   sf::Vector2f(-entity->velocity.x, entity->velocity.y));
    entity->setPos(
        sf::Vector2f(this->position.x + this->size.x, entity->position.y));
  }
  // left
  //  right of entity right of left of platform
  else if (entity->position.x + entity->size.x > this->position.x &&
           entity->position.x + entity->size.x < this->position.x + 2) {
    entity->setVel(damping *
                   sf::Vector2f(-entity->velocity.x, entity->velocity.y));
    entity->setPos(
        sf::Vector2f(this->position.x - entity->size.x, entity->position.y));
  }
}
