#ifndef SPRING_H
#define SPRING_H

#include <SFML/Graphics.hpp>

#include "Platform.h"

class Spring : public Platform {
 public:
  Spring();
  Spring(sf::Vector2f size, sf::Vector2f origin);
};

#endif