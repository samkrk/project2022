#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include <string>

class Game
{
private:
  float gameSpeed;
  std::string gameName;
  sf::RenderWindow win;

  Player player;


  float drag;
  float damping;
  float gravity;
  float jumpPower;
  float jumpPowerHoz;
 public:
  Game();
  void readInputs(Player *player);
  void collision(Entity *entity);
  void calcPosition(Entity *entity);
  void calcPositionDrag(Entity *entity);
  void run();

};

#endif
