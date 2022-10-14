#include "Level.h"

Level::Level() {
  platforms = NULL;
  this->numPlatforms = 0;

  enemies = NULL;
  this->numEnemies = 0;

  coins = NULL;
  this->numCoins = 0;
  this->numCoinsCollected = 0;
}

bool Level::isFinished() {
  if (numCoinsCollected == numCoins)
  {
    return true;
  }
  return false;
}

void Level::addPlatform(Platform newPlatform) {
  Platform *oldPlatfroms = platforms;
  this->numPlatforms++;
  this->platforms = new Platform[numPlatforms];

  // copy oldplatforms back to platfroms and add newplatfrom
  for (int i = 0; i < numPlatforms - 1; i++) {
    platforms[i] = oldPlatfroms[i];
  }
  platforms[numPlatforms - 1] = newPlatform;
}

void Level::newPlatform(sf::Vector2f size, sf::Vector2f origin) {
  Platform newPlatform(size, origin);
  addPlatform(newPlatform);
}

void Level::newSpring(sf::Vector2f size, sf::Vector2f origin) {
  Spring newSpring(size, origin);
  addPlatform(newSpring);
}

void Level::addEnemy(Enemy newEnemy) {
  Enemy *oldEnemies = this->enemies;
  this->numEnemies++;
  this->enemies = new Enemy[numEnemies];

  // copy oldplatforms back to platfroms and add newplatfrom
  for (int i = 0; i < numEnemies - 1; i++) {
    enemies[i] = oldEnemies[i];
  }
  enemies[numEnemies - 1] = newEnemy;
}

void Level::newEnemy(sf::Vector2f origin) {
  Enemy newEnemy(origin);
  addEnemy(newEnemy);
}

void Level::addCoin(Coin newCoin) {
  Coin *oldCoins = this->coins;
  this->numCoins++;
  this->coins = new Coin[numCoins];

  // copy oldplatforms back to platfroms and add newplatfrom
  for (int i = 0; i < numCoins - 1; i++) {
    coins[i] = oldCoins[i];
  }
  coins[numCoins - 1] = newCoin;
}

void Level::newCoin(sf::Vector2f origin) {
  Coin newCoin(origin);
  addCoin(newCoin);
}
