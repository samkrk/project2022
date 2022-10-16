#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Bullet.h"
#include "Coin.h"
#include "Enemy.h"
#include "Entity.h"
#include "Object.h"
#include "Platform.h"
#include "Player.h"
#include "Spring.h"
#include "Level.h"

class Game {
 public:

  std::string gameName;
  sf::RenderWindow win;

  Player player;

  Level *levels;
  int numLevels;
  int levelIndex;

  float gameSpeed;
  float drag;
  float damping;
  float gravity;
  float jumpPower;
  float jumpPowerHoz;

  Game();
  void addLevel(Level newLevel);
  void createLevels();  // for adding platforms and enemies
  void updateLevels();

  void readInputs(Player *player);
  void collisionWithWindow(Entity *entity);
  void calcPosition(Entity *entity);
  void calcPositionDrag(Entity *entity);

  void updateObjects();
  void drawObjects();

  void run();
};

#endif
