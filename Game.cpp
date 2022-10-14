#include "Game.h"

#include <math.h>

#include <iostream>

using namespace std;

Game::Game() {
  this->gameName = "Platform Game";
  this->gameSpeed = 0.02;
  this->drag = 0.0001;  // force oposing velocity
  this->damping = 0.3;  // loss in energy bouncing off walls
  this->gravity = 2.2;
  this->jumpPower = 30;
  this->jumpPowerHoz = 20;

  platforms = NULL;
  this->numPlatforms = 0;

  enemies = NULL;
  this->numEnemies = 0;

  coins = NULL;
  this->numCoins = 0;

  win.create(sf::VideoMode(1800, 1500), gameName);
}

void Game::createLevel() {
  int thickness = 300;
  //newPlatform(sf::Vector2f(100,thickness),sf::Vector2f(100,500));
  newPlatform(sf::Vector2f(300, thickness), sf::Vector2f(200, 1200));
  newPlatform(sf::Vector2f(400, thickness), sf::Vector2f(300, 1000));
  newPlatform(sf::Vector2f(600, thickness), sf::Vector2f(800, 800));
  newPlatform(sf::Vector2f(1000, thickness), sf::Vector2f(900, 100));
  newSpring(sf::Vector2f(20, thickness), sf::Vector2f(20, 600));
  newSpring(sf::Vector2f(400, 10), sf::Vector2f(140, 800));

  for (int i = 400; i < 1600; i+=100)
  {
    newEnemy(sf::Vector2f(i, i));
  }
  
  for (int i = 100; i < 1600; i+=50)
  {
    newCoin(sf::Vector2f(i,500));
  }
  

}

void Game::addPlatform(Platform newPlatform) {
  Platform *oldPlatfroms = platforms;
  this->numPlatforms++;
  this->platforms = new Platform[numPlatforms];

  // copy oldplatforms back to platfroms and add newplatfrom
  for (int i = 0; i < numPlatforms - 1; i++) {
    platforms[i] = oldPlatfroms[i];
  }
  platforms[numPlatforms - 1] = newPlatform;
}

void Game::newPlatform(sf::Vector2f size, sf::Vector2f origin) {
  Platform newPlatform(size, origin);
  addPlatform(newPlatform);
}

void Game::newSpring(sf::Vector2f size, sf::Vector2f origin) {
  Spring newSpring(size,origin);
  addPlatform(newSpring);
}

void Game::addEnemy(Enemy newEnemy){
  Enemy *oldEnemies = this->enemies;
  this->numEnemies++;
  this->enemies = new Enemy[numEnemies];

  // copy oldplatforms back to platfroms and add newplatfrom
  for (int i = 0; i < numEnemies - 1; i++) {
    enemies[i] = oldEnemies[i];
  }
  enemies[numEnemies - 1] = newEnemy;
}

void Game::newEnemy(sf::Vector2f origin){
  Enemy newEnemy(origin);
  addEnemy(newEnemy);
}

void Game::addCoin(Coin newCoin) {
  Coin *oldCoins = this->coins;
  this->numCoins++;
  this->coins = new Coin[numCoins];

  // copy oldplatforms back to platfroms and add newplatfrom
  for (int i = 0; i < numCoins - 1; i++) {
    coins[i] = oldCoins[i];
  }
  coins[numCoins - 1] = newCoin;
}

void Game::newCoin(sf::Vector2f origin) {
  Coin newCoin(origin);
  addCoin(newCoin);
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

  for (int i = 0; i < numEnemies; i++) {
    player.isKilled(&enemies[i]);
  }

  if (player.isAlive) {
    collisionWithWindow(&player);

    for (int i = 0; i < numPlatforms; i++) {
      platforms[i].collisionPhysics(&player);
    }

    readInputs(&player);

    calcPositionDrag(&player);
  }

  // update enemies

  for (int i = 0; i < numEnemies; i++) {
    enemies[i].isShot(&player);
  }

  for (int p = 0; p < numPlatforms; p++) {
    for (int e = 0; e < numEnemies; e++) {
      if (enemies[e].isAlive) {
        platforms[p].collisionPhysics(&enemies[e]);
      }
    }
  }

  for (int i = 0; i < numEnemies; i++) {
    if (enemies[i].isAlive) {
      collisionWithWindow(&enemies[i]);
      enemies[i].move(&player);
      calcPositionDrag(&enemies[i]);
    }
  }
  // update coins

  for (int i = 0; i < numCoins; i++) {
    coins[i].playerCollect(&player);
  }

  // update bullets

  for (int i = 0; i < player.magSize; i++) {
    calcPosition(&player.bullets[i]);
  }
}

void Game::drawObjects() {
  // display objects to screen

  this->win.clear();
  // platforms
  for (int i = 0; i < numPlatforms; i++) {
    win.draw(platforms[i].body);
  }

  // player
  win.draw(player.body);

  // enemies

  for (int i = 0; i < numEnemies; i++) {
    win.draw(enemies[i].body);
  }
  // coins
  for (int i = 0; i < numCoins; i++) {
    win.draw(coins[i].body);
  }

  // bullets
  for (int i = 0; i < player.magSize; i++) {
    win.draw(player.bullets[i].body);
  }

  this->win.display();
}

void Game::run() {
  // spawn and draw nessasery objects
    createLevel();
  // game loop
  while (win.isOpen()) {
    sf::Event event;
    while (win.pollEvent(event)) {
      if (event.type == sf::Event::Closed) win.close();
    }

    updateObjects();

    drawObjects();
  
  }
}