#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Bullet.h"
#include "Enemy.h"
#include "Entity.h"
#include "Object.h"
#include "Platform.h"
#include "Player.h"
#include "Spring.h"

class Game {
 public:
  float gameSpeed;
  std::string gameName;
  sf::RenderWindow win;

  Platform *platforms;
  int numPlatforms;

  Player player;

  Enemy *enemies;
  int numEnemies;

  float drag;
  float damping;
  float gravity;
  float jumpPower;
  float jumpPowerHoz;

  Game();

  void createLevel();  // for adding platforms and enemies
  void addPlatform(Platform newPlatform);
  // deals with dynamic mem ^^
  void newPlatform(sf::Vector2f size, sf::Vector2f origin);
  void newSpring(sf::Vector2f size, sf::Vector2f origin);

  void addEnemy(Enemy newEnemy);
  void newEnemy(sf::Vector2f origin);

  void readInputs(Player *player);
  void collisionWithWindow(Entity *entity);
  void calcPosition(Entity *entity);
  void calcPositionDrag(Entity *entity);
  void run();
};

#endif
