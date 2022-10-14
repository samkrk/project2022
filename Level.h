#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Coin.h"
#include "Enemy.h"
#include "Platform.h"
#include "Spring.h"

class Level
{
public:

 sf::Vector2f spawnCoords;

 Platform *platforms;
 int numPlatforms;

 Enemy *enemies;
 int numEnemies;

 Coin *coins;
 int numCoins;
 int numCoinsCollected;

 Level();

 bool isFinished();

 void addPlatform(Platform newPlatform);
 void newPlatform(sf::Vector2f size, sf::Vector2f origin);
 void newSpring(sf::Vector2f size, sf::Vector2f origin);

 void addEnemy(Enemy newEnemy);
 void newEnemy(sf::Vector2f origin);

 void addCoin(Coin newCoin);
 void newCoin(sf::Vector2f origin);

};



#endif