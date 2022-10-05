#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>

class Player : public Entity {
 public:
 void print() {
   std::cout << "Hello" << std::endl;
 }
  
    
};

#endif