#include "Game.h"

#include <math.h>

#include <iostream>

using namespace std;

Game::Game() { // game constructor needs to initialise everything 
  time.asSeconds(); // timer 
  isCompleteLevels = false;

  this->gameName = "Platform Game";
  this->gameSpeed = 0.02;
  this->drag = 0.0001;  // force oposing velocity
  this->damping = 0.3;  // loss in energy bouncing off walls
  this->gravity = 2.2;
  this->jumpPower = 30;
  this->jumpPowerHoz = 20;

  // initialise level settings 
  levels = NULL;
  numLevels = 0;
  int levelIndex = 0;

  win.create(sf::VideoMode(1800, 1500), gameName); // create window

  // load fonts and textures from files 
  font.loadFromFile("arcadefont.TTF");
  background.loadFromFile("background4.jpeg");
  bg.setTexture(background);
  bg.setScale(1.12,1.4);
  platformTexture.loadFromFile("platformskin.png");
  coinTexture.loadFromFile("coinskin.png");
  springTexture.loadFromFile("springart.png");
  playerTexture.loadFromFile("trollskin.png");
  VertPlatformTexture.loadFromFile("1by2platform.png");
  VertSpringTexture.loadFromFile("verticalspring.png");
  enemyTexture.loadFromFile("enemy.png");

  // set up the words in the top left corner of game 
  levelStat.setFont(font);
  levelStat.setFillColor(sf::Color::White);
  levelStat.setPosition(20, 10);
  levelStat.setCharacterSize(75);

  bulletsLeft.setFont(font);
  bulletsLeft.setFillColor(sf::Color::Red);
  bulletsLeft.setPosition(20, 200);
  bulletsLeft.setCharacterSize(30);

  timer.setFont(font);
  timer.setFillColor(sf::Color::White);
  timer.setPosition(20, 100);
  timer.setCharacterSize(75);
}

void Game::addLevel(Level newLevel) { // used to index the levels 
  Level *oldLevels = levels;
  this->numLevels++;
  this->levels = new Level[numLevels];

  // copy oldplatforms back to platfroms and add newplatfrom
  for (int i = 0; i < numLevels - 1; i++) {
    levels[i] = oldLevels[i];
  }
  levels[numLevels - 1] = newLevel;
}

void Game::createLevels() { // initialises all the levels 
  levels = NULL;
  numLevels = 0;
  int levelIndex = 0;
  player.body.setTexture(&playerTexture);
  player.body.setOutlineColor(sf::Color::Transparent);
  player.body.setFillColor(sf::Color::White);
  // level 1
  Level newLevel;
  addLevel(newLevel);
  // spawd coords
  levels[numLevels - 1].spawnCoords = sf::Vector2f(100,1450);

  // platforms 
  levels[numLevels - 1].newPlatform(sf::Vector2f(500, 75),sf::Vector2f(300, 1325));
  levels[numLevels - 1].platforms[0].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(400, 75),sf::Vector2f(1100, 900));
  levels[numLevels - 1].platforms[1].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 300),sf::Vector2f(800, 100));
  levels[numLevels - 1].platforms[2].body.setTexture(&VertPlatformTexture);

  // springs
  levels[numLevels - 1].newSpring(sf::Vector2f(50, 300),sf::Vector2f(300, 200));
  levels[numLevels - 1].platforms[3].body.setTexture(&springTexture); 
  levels[numLevels - 1].newSpring(sf::Vector2f(500, 50),sf::Vector2f(700, 600));
  levels[numLevels - 1].platforms[4].body.setTexture(&springTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(50, 200),sf::Vector2f(1300, 500));
  levels[numLevels - 1].platforms[5].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(200, 50),sf::Vector2f(900, 1125));
  levels[numLevels - 1].platforms[6].body.setTexture(&springTexture);

  // enemies
  levels[numLevels - 1].newEnemy(sf::Vector2f(1350, 850));
  levels[numLevels - 1].enemies[0].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(750, 1300));
  levels[numLevels - 1].enemies[1].body.setTexture(&enemyTexture);

  // coins
  levels[numLevels - 1].newCoin(sf::Vector2f(700, 100));
  levels[numLevels - 1].coins[0].body.setTexture(&coinTexture);

  // level 2
  addLevel(newLevel);
  // spawn coords
  levels[numLevels - 1].spawnCoords = sf::Vector2f(1600,350);

  // spring
  levels[numLevels - 1].newSpring(sf::Vector2f(50, 100),sf::Vector2f(1750, 200));
  levels[numLevels - 1].platforms[0].body.setTexture(&springTexture);   

  // platforms 
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1600, 400)); 
  levels[numLevels - 1].platforms[1].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1400, 600));
  levels[numLevels - 1].platforms[2].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1200, 600));
  levels[numLevels - 1].platforms[3].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1000, 400));
  levels[numLevels - 1].platforms[4].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(900, 600));
  levels[numLevels - 1].platforms[5].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(700, 600));
  levels[numLevels - 1].platforms[6].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(500, 400));
  levels[numLevels - 1].platforms[7].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 50),sf::Vector2f(0, 400));
  levels[numLevels - 1].platforms[8].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(800, 1100));
  levels[numLevels - 1].platforms[9].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1500, 1200));
  levels[numLevels - 1].platforms[10].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1400, 900));
  levels[numLevels - 1].platforms[11].body.setTexture(&platformTexture);

  // vertical platforms
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 400),sf::Vector2f(300, 500));
  levels[numLevels - 1].platforms[12].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 400),sf::Vector2f(300, 1100));
  levels[numLevels - 1].platforms[13].body.setTexture(&VertPlatformTexture);

  // springs
  levels[numLevels - 1].newSpring(sf::Vector2f(300, 150),sf::Vector2f(100, 50));
  levels[numLevels - 1].platforms[14].body.setTexture(&springTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(75, 150),sf::Vector2f(850, 700));
  levels[numLevels - 1].platforms[15].body.setTexture(&VertSpringTexture);

  // enemies
  levels[numLevels - 1].newEnemy(sf::Vector2f(1400, 500));
  levels[numLevels - 1].enemies[0].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(1250, 500));
  levels[numLevels - 1].enemies[1].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(900, 500));
  levels[numLevels - 1].enemies[2].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(750, 500));
  levels[numLevels - 1].enemies[3].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(20, 1400));
  levels[numLevels - 1].enemies[4].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(140, 1400));
  levels[numLevels - 1].enemies[5].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(1100, 1400));
  levels[numLevels - 1].enemies[6].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(1300, 1100));
  levels[numLevels - 1].enemies[7].body.setTexture(&enemyTexture);

  // coins
  levels[numLevels - 1].newCoin(sf::Vector2f(1300, 300));
  levels[numLevels - 1].coins[0].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(0, 300));
  levels[numLevels - 1].coins[1].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(1500, 800));
  levels[numLevels - 1].coins[2].body.setTexture(&coinTexture);
  

  // level 3
  addLevel(newLevel);

  // spawn coords
  levels[numLevels - 1].spawnCoords = sf::Vector2f(100,1450);

  // spring
  levels[numLevels - 1].newSpring(sf::Vector2f(100, 200),sf::Vector2f(200, 900));
  levels[numLevels - 1].platforms[0].body.setTexture(&springTexture);   

  // platforms
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(0, 1000)); //1 
  levels[numLevels - 1].platforms[1].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(600, 800)); //2
  levels[numLevels - 1].platforms[2].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 100),sf::Vector2f(1000, 1050));//3
  levels[numLevels - 1].platforms[3].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1400, 1100));//4
  levels[numLevels - 1].platforms[4].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1100, 550));//5
  levels[numLevels - 1].platforms[5].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(500, 200));//6
  levels[numLevels - 1].platforms[6].body.setTexture(&platformTexture);

  // vertical platforms
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 400),sf::Vector2f(100, 500));//7
  levels[numLevels - 1].platforms[7].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(400, 100),sf::Vector2f(300, 450));//8
  levels[numLevels - 1].platforms[8].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(150, 300),sf::Vector2f(600, 1200));//9
  levels[numLevels - 1].platforms[9].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(30, 320),sf::Vector2f(970, 180));//10
  levels[numLevels - 1].platforms[10].body.setTexture(&VertPlatformTexture);

  // springs 
  levels[numLevels - 1].newSpring(sf::Vector2f(100, 200),sf::Vector2f(600, 1000));
  levels[numLevels - 1].platforms[11].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(400, 100),sf::Vector2f(700, 500));//12
  levels[numLevels - 1].platforms[12].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(100, 200),sf::Vector2f(1000, 700));//13
  levels[numLevels - 1].platforms[13].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(300, 100),sf::Vector2f(900, 1400));//14
  levels[numLevels - 1].platforms[14].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(100, 200),sf::Vector2f(1700, 600));//15
  levels[numLevels - 1].platforms[15].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(100, 200),sf::Vector2f(1200, 100));//16
  levels[numLevels - 1].platforms[16].body.setTexture(&VertSpringTexture);

  // enemies
  levels[numLevels - 1].newEnemy(sf::Vector2f(700, 700));
  levels[numLevels - 1].enemies[0].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(1400, 1450));
  levels[numLevels - 1].enemies[1].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(800, 400));
  levels[numLevels - 1].enemies[2].body.setTexture(&enemyTexture);

  // coins
  levels[numLevels - 1].newCoin(sf::Vector2f(1500, 1000));
  levels[numLevels - 1].coins[0].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(500, 80));
  levels[numLevels - 1].coins[1].body.setTexture(&coinTexture);
  
  // level 4
  addLevel(newLevel);

  levels[numLevels - 1].spawnCoords = sf::Vector2f(50,600);

  levels[numLevels - 1].newSpring(sf::Vector2f(100, 300),sf::Vector2f(1700, 900));
  levels[numLevels - 1].platforms[0].body.setTexture(&springTexture);   

  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(0, 200)); //1 
  levels[numLevels - 1].platforms[1].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(300, 300)); //2
  levels[numLevels - 1].platforms[2].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(300, 100),sf::Vector2f(0, 700));//3
  levels[numLevels - 1].platforms[3].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(200, 1300));//4
  levels[numLevels - 1].platforms[4].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(500, 1100));//5
  levels[numLevels - 1].platforms[5].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1100, 1100));//6
  levels[numLevels - 1].platforms[6].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1400, 1300));//7
  levels[numLevels - 1].platforms[7].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(300, 100),sf::Vector2f(1500, 700));//8
  levels[numLevels - 1].platforms[8].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1300, 300));//9
  levels[numLevels - 1].platforms[9].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1600, 200));//10
  levels[numLevels - 1].platforms[10].body.setTexture(&platformTexture);

  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 200),sf::Vector2f(800, 1300));//11
  levels[numLevels - 1].platforms[11].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 400),sf::Vector2f(700, 300));//12
  levels[numLevels - 1].platforms[12].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 400),sf::Vector2f(1000, 300));//13
  levels[numLevels - 1].platforms[13].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 200),sf::Vector2f(400, 400));//14
  levels[numLevels - 1].platforms[14].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 100),sf::Vector2f(600, 1000));//15
  levels[numLevels - 1].platforms[15].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 100),sf::Vector2f(1100, 1000));//16
  levels[numLevels - 1].platforms[16].body.setTexture(&VertPlatformTexture);

  
  levels[numLevels - 1].newSpring(sf::Vector2f(100, 300),sf::Vector2f(0, 900));//17
  levels[numLevels - 1].platforms[17].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(200, 100),sf::Vector2f(300, 0));//18
  levels[numLevels - 1].platforms[18].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(200, 100),sf::Vector2f(600, 900));//19
  levels[numLevels - 1].platforms[19].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(200, 100),sf::Vector2f(1000, 900));//20
  levels[numLevels - 1].platforms[20].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(200, 100),sf::Vector2f(1300, 0));//21
  levels[numLevels - 1].platforms[21].body.setTexture(&VertSpringTexture);

  levels[numLevels - 1].newEnemy(sf::Vector2f(0, 1450));
  levels[numLevels - 1].enemies[0].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(1750, 1450));
  levels[numLevels - 1].enemies[1].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(1700, 650));
  levels[numLevels - 1].enemies[2].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(700, 250));
  levels[numLevels - 1].enemies[3].body.setTexture(&enemyTexture);



  levels[numLevels - 1].newCoin(sf::Vector2f(50, 100));
  levels[numLevels - 1].coins[0].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(1750, 100));
  levels[numLevels - 1].coins[1].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(900, 450));
  levels[numLevels - 1].coins[2].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(750, 1050));
  levels[numLevels - 1].coins[3].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(1000, 1050));
  levels[numLevels - 1].coins[4].body.setTexture(&coinTexture);


  // level 5
  addLevel(newLevel);

  levels[numLevels - 1].spawnCoords = sf::Vector2f(100,50);

  levels[numLevels - 1].newSpring(sf::Vector2f(100, 300),sf::Vector2f(1700, 500));
  levels[numLevels - 1].platforms[0].body.setTexture(&springTexture);   

  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(0, 100)); //1 
  levels[numLevels - 1].platforms[1].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 100),sf::Vector2f(400, 1000)); //2
  levels[numLevels - 1].platforms[2].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(600, 1200));//3
  levels[numLevels - 1].platforms[3].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(300, 100),sf::Vector2f(700, 900));//4
  levels[numLevels - 1].platforms[4].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 100),sf::Vector2f(1100, 1100));//5
  levels[numLevels - 1].platforms[5].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1100, 700));//6
  levels[numLevels - 1].platforms[6].body.setTexture(&platformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1600, 100));//7
  levels[numLevels - 1].platforms[7].body.setTexture(&platformTexture);

  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 300),sf::Vector2f(0, 1200));//8
  levels[numLevels - 1].platforms[8].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 600),sf::Vector2f(200, 400));//9
  levels[numLevels - 1].platforms[9].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 200),sf::Vector2f(500, 500));//10
  levels[numLevels - 1].platforms[10].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 300),sf::Vector2f(500, 0));//11
  levels[numLevels - 1].platforms[11].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 800),sf::Vector2f(800, 0));//12
  levels[numLevels - 1].platforms[12].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 200),sf::Vector2f(900, 1300));//13
  levels[numLevels - 1].platforms[13].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 300),sf::Vector2f(1400, 800));//14
  levels[numLevels - 1].platforms[14].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 300),sf::Vector2f(1600, 1200));//15
  levels[numLevels - 1].platforms[15].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(200, 100),sf::Vector2f(1200, 400));//16
  levels[numLevels - 1].platforms[16].body.setTexture(&VertPlatformTexture);
  levels[numLevels - 1].newPlatform(sf::Vector2f(100, 100),sf::Vector2f(1700, 400));//17
  levels[numLevels - 1].platforms[17].body.setTexture(&VertPlatformTexture);

  
  levels[numLevels - 1].newSpring(sf::Vector2f(200, 100),sf::Vector2f(200, 1400));//18
  levels[numLevels - 1].platforms[18].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(200, 100),sf::Vector2f(1400, 1400));//19
  levels[numLevels - 1].platforms[19].body.setTexture(&VertSpringTexture);
  levels[numLevels - 1].newSpring(sf::Vector2f(200, 100),sf::Vector2f(1200, 300));//20
  levels[numLevels - 1].platforms[20].body.setTexture(&VertSpringTexture);


  levels[numLevels - 1].newEnemy(sf::Vector2f(50, 1100));
  levels[numLevels - 1].enemies[0].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(1200, 1450));
  levels[numLevels - 1].enemies[1].body.setTexture(&enemyTexture);
  levels[numLevels - 1].newEnemy(sf::Vector2f(1750, 300));
  levels[numLevels - 1].enemies[2].body.setTexture(&enemyTexture);



  levels[numLevels - 1].newCoin(sf::Vector2f(25, 600));
  levels[numLevels - 1].coins[0].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(425, 900));
  levels[numLevels - 1].coins[1].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(1125, 1050));
  levels[numLevels - 1].coins[2].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(725, 80));
  levels[numLevels - 1].coins[3].body.setTexture(&coinTexture);
  levels[numLevels - 1].newCoin(sf::Vector2f(1650, 25));
  levels[numLevels - 1].coins[4].body.setTexture(&coinTexture);
}

void Game::readInputs(Player *player) {
  // player movement input

  player->setAcc(sf::Vector2f(0, gravity));

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    player->addAcc(sf::Vector2f(-player->speed, 0));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    player->addAcc(sf::Vector2f(player->speed, 0));
  }
  // probably get rid of up with jump command now
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    player->addAcc(sf::Vector2f(0, -player->speed));
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    player->addAcc(sf::Vector2f(0, player->speed));
  }
  // Jump input
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    if (player->onGround) {
      player->setVel(sf::Vector2f(0, -this->jumpPower * player->speed));
    }
    if (player->onLWall) {
      player->setVel(player->speed *
                     sf::Vector2f(this->jumpPowerHoz, -this->jumpPower));
    }
    if (player->onRWall) {
      player->setVel(player->speed *
                     sf::Vector2f(-this->jumpPowerHoz, -this->jumpPower));
    }
  }
  // shooting input

  player->time = player->clock.getElapsedTime();
  player->timeSinceShot = player->time.asMilliseconds();

  if (player->bulletIndex < player->magSize &&
      player->timeSinceShot > player->fireRate && !player->reloading) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      player->shoot(-1);
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      player->shoot(1);
    }
  }
  // reload
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || player->reloading) {
    if (!player->reloading) {
      player->clock.restart();  // starts reload delay
    }
    player->reload();
    std::cout << "Reloading: ";
    std::cout << (1000 - player->timeSinceShot) / 1000 << "sec remaining"
              << std::endl;
  }
}

void Game::calcPosition(Entity *entity) {
  entity->addVel(entity->acceleration * this->gameSpeed);
  entity->addPos(entity->velocity * this->gameSpeed);
  entity->update();
}

void Game::calcPositionDrag(Entity *entity) {
  float velocityMag = pow(entity->velocity.x, 2) + pow(entity->velocity.y, 2);
  entity->addAcc(-entity->velocity * this->drag *
                 velocityMag);  // drag F prop kv^2, therefore a = kv^2
  calcPosition(entity);
}

void Game::collisionWithWindow(Entity *entity) {
  // floor
  if (entity->position.y > win.getSize().y - entity->size.y) {
    entity->setPos(
        sf::Vector2f(entity->position.x, win.getSize().y - entity->size.y));
    if (!entity->onPlatform) {
      entity->setVel(damping *
                     sf::Vector2f(entity->velocity.x, -entity->velocity.y));
    }
  }

  // top
  if (entity->position.y < 0) {
    entity->setVel(damping *
                   sf::Vector2f(entity->velocity.x, -entity->velocity.y));
    entity->setPos(sf::Vector2f(entity->position.x, 0));
  }
  // right
  if (entity->position.x > win.getSize().x - entity->size.x) {
    entity->setVel(damping *
                   sf::Vector2f(-entity->velocity.x, entity->velocity.y));
    entity->setPos(
        sf::Vector2f(win.getSize().x - entity->size.x, entity->position.y));
  }
  // left
  if (entity->position.x < 0) {
    entity->setVel(damping *
                   sf::Vector2f(-entity->velocity.x, entity->velocity.y));
    entity->setPos(sf::Vector2f(0, entity->position.y));
  }

  if (entity->position.y > win.getSize().y - entity->size.y - 0.0000001) {
    entity->onPlatform = true;
    entity->onGround = true;
  } else if (entity->position.x >
             win.getSize().x - entity->size.x - 0.0000001) {
    entity->onPlatform = true;
    entity->onRWall = true;
  } else if (entity->position.x < 0 + 0.000001) {
    entity->onPlatform = true;
    entity->onLWall = true;
  } else {
    entity->onPlatform = false;
    entity->onGround = false;
    entity->onLWall = false;
    entity->onRWall = false;
  }
}

void Game::updateObjects() {
  // update player

  for (int i = 0; i < levels[levelIndex].numEnemies; i++) {
    player.isKilled(&levels[levelIndex].enemies[i]);
  }

  if (player.isAlive) {
    collisionWithWindow(&player);

    for (int i = 0; i < levels[levelIndex].numPlatforms; i++) {
      levels[levelIndex].platforms[i].collisionPhysics(&player);
    }

    readInputs(&player);

    calcPositionDrag(&player);
  } else {
    createLevels();
    player.respawn(levels[levelIndex].spawnCoords);
  }

  // update enemies

  for (int i = 0; i < levels[levelIndex].numEnemies; i++) {
    levels[levelIndex].enemies[i].isShot(&player);
  }

  for (int p = 0; p < levels[levelIndex].numPlatforms; p++) {
    for (int e = 0; e < levels[levelIndex].numEnemies; e++) {
      if (levels[levelIndex].enemies[e].isAlive) {
        levels[levelIndex].platforms[p].collisionPhysics(
            &levels[levelIndex].enemies[e]);
      }
    }
  }

  for (int i = 0; i < levels[levelIndex].numEnemies; i++) {
    if (levels[levelIndex].enemies[i].isAlive) {
      collisionWithWindow(&levels[levelIndex].enemies[i]);
      levels[levelIndex].enemies[i].move(&player);
      calcPositionDrag(&levels[levelIndex].enemies[i]);
    }
  }
  // update coins
  for (int i = 0; i < levels[levelIndex].numCoins; i++) {
    levels[levelIndex].coins[i].playerCollect(&player);
  }

  // update bullets
  for (int i = 0; i < player.magSize; i++) {
    calcPosition(&player.bullets[i]);
  }

  // update time
  time = clock.getElapsedTime();
  gameTime = time.asSeconds();
}

void Game::drawObjects() {
  // display objects to screen

  this->win.clear();
  // background 
  win.draw(bg);

  // platforms
  for (int i = 0; i < levels[levelIndex].numPlatforms; i++) {
    win.draw(levels[levelIndex].platforms[i].body);
  }

  // player
  win.draw(player.body);

  // enemies

  for (int i = 0; i < levels[levelIndex].numEnemies; i++) {
    win.draw(levels[levelIndex].enemies[i].body);
  }
  // coins
  for (int i = 0; i < levels[levelIndex].numCoins; i++) {
    win.draw(levels[levelIndex].coins[i].body);
  }
  

  // bullets
  for (int i = 0; i < player.magSize; i++) {
    win.draw(player.bullets[i].body);
  }

  // stats
  win.draw(levelStat);
  win.draw(bulletsLeft);
  win.draw(timer);

  this->win.display();
}

void Game::updateLevels() {
  levels[levelIndex].countCoinsCollected();

  if (levels[levelIndex].isFinished()) {
    levelIndex++;
    player.respawn(levels[levelIndex].spawnCoords);
  }
  if (levelIndex == numLevels) {
    isCompleteLevels = true;
  }
}

void Game::updateGameStats() {
  sf::String str;

  str = "Level  ";
  str += std::to_string(levelIndex + 1);
  str += " of ";
  str += std::to_string(numLevels);

  levelStat.setString(str);

  str = std::to_string(player.magSize - player.bulletIndex);
  str += "   of   ";
  str += std::to_string(player.magSize);
  str += "  bullets      r   to  reload";

  bulletsLeft.setString(str);

  str = std::to_string(gameTime);
  str += " s";

  timer.setString(str);
}

void Game::gameLoop() {
  isCompleteLevels = false;
  createLevels();  // spawn and draw nessasery objects
  levelIndex = 0;
  // game loop
  while (win.isOpen() && !isCompleteLevels) {
    sf::Event event;
    while (win.pollEvent(event)) {
      if (event.type == sf::Event::Closed) win.close();
    }

    updateGameStats();

    updateObjects();

    drawObjects();

    updateLevels();
  }
}

void Game::run() {
  while (win.isOpen()) {
    sf::Event event;
    while (win.pollEvent(event)) {
      if (event.type == sf::Event::Closed) win.close();
    }

    menu.displayMenu(&win);

    if (menu.playSelected) {
      menu.displayHowToPlay(&win);

      clock.restart();  // start game timer
      isCompleteLevels = false;

      gameLoop();

      // game complete
      time = clock.getElapsedTime();
      gameTime = time.asSeconds();

      if (isCompleteLevels)
      {
        highscores.write(gameTime);
      }

      menu.displayWinScreen(&win, gameTime, highscores.highscore);

      highscores.read();  // update highscore

    } else {
      menu.displayLeaderBoard(&win, highscores.highscore);
    }
  }
}