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
#include "Menu.h"
#include "Highscores.h"

class Game {
 public:
  sf::Clock clock;
  sf::Time time;
  bool isCompleteLevels;
  float timeSinceShot;
  int gameTime;

  Highscores highscores;

  Menu menu;

  float gameSpeed;
  std::string gameName;
  sf::RenderWindow win;

  Player player;

  Level *levels;
  int numLevels;
  int levelIndex;

  float drag;
  float damping;
  float gravity;
  float jumpPower;
  float jumpPowerHoz;

  sf::Font font;
  sf::Text levelStat;
  sf::Text bulletsLeft;
  sf::Text timer;

  sf::Texture background;
  sf::Sprite bg;

  sf::Texture platformTexture;
  sf::Texture coinTexture;
  sf::Texture springTexture;
  sf::Texture playerTexture;
  sf::Texture VertSpringTexture;
  sf::Texture VertPlatformTexture;
  sf::Texture enemyTexture;

  Game();

  void gameLoop();

  void addLevel(Level newLevel);
  void createLevels();  // for adding platforms and enemies
  void updateLevels();

  void addPlatform(Platform newPlatform);
  // deals with dynamic mem ^^
  void newPlatform(sf::Vector2f size, sf::Vector2f origin);
  void newSpring(sf::Vector2f size, sf::Vector2f origin);

  void addEnemy(Enemy newEnemy);
  void newEnemy(sf::Vector2f origin);

  void addCoin(Coin newCoin);
  void newCoin(sf::Vector2f origin);

  void readInputs(Player *player);
  void collisionWithWindow(Entity *entity);
  void calcPosition(Entity *entity);
  void calcPositionDrag(Entity *entity);

  void updateObjects();
  void drawObjects();

  void updateGameStats();

  void run();
};

#endif
