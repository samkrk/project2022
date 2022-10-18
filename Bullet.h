#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Bullet : public Entity {
 public:
  bool isFired;

  Bullet();
  Bullet(float speed);

  void print();
};

#endif