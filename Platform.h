#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Platform : public Object {
 public:
  float damping;

  Platform();
  Platform(sf::Vector2f size, sf::Vector2f origin);

  bool collision(Entity *entity);
  void collisionPhysics(Entity *entity);
};

#endif