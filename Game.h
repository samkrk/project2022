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
  // members required for timer 
  sf::Clock clock; 
  sf::Time time;
  bool isCompleteLevels;
  float timeSinceShot;
  int gameTime;

  // highscores class member 
  Highscores highscores;

  // game must have a menu 
  Menu menu;

  // determines overall speed of game
  float gameSpeed;
  std::string gameName;
  sf::RenderWindow win; // game window

  // player class object
  Player player;

  // levels array with level index 
  Level *levels;
  int numLevels;
  int levelIndex;
  
  // ingame variables 
  float drag;
  float damping;
  float gravity;
  float jumpPower;
  float jumpPowerHoz;


  sf::Font font; // font for stats text
  sf::Text levelStat; // texts for stats, timer etc 
  sf::Text bulletsLeft;
  sf::Text timer;

  // background texture and sprite
  sf::Texture background;
  sf::Sprite bg;

  // textures for all the drawable entities
  sf::Texture platformTexture;
  sf::Texture coinTexture;
  sf::Texture springTexture;
  sf::Texture playerTexture;
  sf::Texture VertSpringTexture;
  sf::Texture VertPlatformTexture;
  sf::Texture enemyTexture;

  Game(); // game constructor 

  void gameLoop(); // game loop

  void addLevel(Level newLevel); // to create a new level
  void createLevels();  // for adding platforms and enemies
  void updateLevels();

  void addPlatform(Platform newPlatform);
  // deals with dynamic mem ^^
  void newPlatform(sf::Vector2f size, sf::Vector2f origin);
  void newSpring(sf::Vector2f size, sf::Vector2f origin);

  void addEnemy(Enemy newEnemy); 
  void newEnemy(sf::Vector2f origin); // create new enemy

  void addCoin(Coin newCoin);
  void newCoin(sf::Vector2f origin); // create new coin

  void readInputs(Player *player); // take user input
  void collisionWithWindow(Entity *entity); // game physics
  void calcPosition(Entity *entity); // game physics
  void calcPositionDrag(Entity *entity); // game physics

  void updateObjects(); // move objects by amount determined in game physics 
  void drawObjects(); // clear window and draw everything 

  void updateGameStats(); // update game statistics 

  void run(); // combination of all above funcitons
};

#endif
