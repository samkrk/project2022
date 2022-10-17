#include "Game.h"

#include <math.h>

#include <iostream>

using namespace std;

Game::Game() {
  time.asSeconds();
  isCompleteLevels = false;

  this->gameName = "Platform Game";
  this->gameSpeed = 0.02;
  this->drag = 0.0001;  // force oposing velocity
  this->damping = 0.3;  // loss in energy bouncing off walls
  this->gravity = 2.2;
  this->jumpPower = 30;
  this->jumpPowerHoz = 20;

  levels = NULL;
  numLevels = 0;
  int levelIndex = 0;

  win.create(sf::VideoMode(1800, 1500), gameName);

  font.loadFromFile("arcadefont.TTF");

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

void Game::addLevel(Level newLevel) {
  Level *oldLevels = levels;
  this->numLevels++;
  this->levels = new Level[numLevels];

  // copy oldplatforms back to platfroms and add newplatfrom
  for (int i = 0; i < numLevels - 1; i++) {
    levels[i] = oldLevels[i];
  }
  levels[numLevels - 1] = newLevel;
}

void Game::createLevels() {
  levels = NULL;
  numLevels = 0;
  int levelIndex = 0;
  // level 1
  Level newLevel;
  addLevel(newLevel);

  int thickness = 300;
  levels[numLevels - 1].newPlatform(sf::Vector2f(300, thickness),
                                    sf::Vector2f(200, 1200));
  levels[numLevels - 1].newPlatform(sf::Vector2f(400, thickness),
                                    sf::Vector2f(300, 1000));
  levels[numLevels - 1].newPlatform(sf::Vector2f(600, thickness),
                                    sf::Vector2f(800, 800));
  levels[numLevels - 1].newPlatform(sf::Vector2f(1000, thickness),
                                    sf::Vector2f(900, 100));
  levels[numLevels - 1].newSpring(sf::Vector2f(20, thickness),
                                  sf::Vector2f(20, 600));
  levels[numLevels - 1].newSpring(sf::Vector2f(400, 10),
                                  sf::Vector2f(140, 800));

  for (int i = 400; i < 1600; i += 100) {
    levels[numLevels - 1].newEnemy(sf::Vector2f(i, i));
  }

  for (int i = 100; i < 200; i += 50) {
    levels[numLevels - 1].newCoin(sf::Vector2f(i, 500));
  }

  // level 2
  addLevel(newLevel);

  levels[numLevels - 1].spawnCoords = sf::Vector2f(1000, 600);

  levels[numLevels - 1].newPlatform(sf::Vector2f(300, thickness),
                                    sf::Vector2f(200, 1200));
  levels[numLevels - 1].newPlatform(sf::Vector2f(400, thickness),
                                    sf::Vector2f(300, 1000));
  levels[numLevels - 1].newPlatform(sf::Vector2f(600, thickness),
                                    sf::Vector2f(800, 800));
  levels[numLevels - 1].newPlatform(sf::Vector2f(1000, thickness),
                                    sf::Vector2f(900, 100));
  levels[numLevels - 1].newSpring(sf::Vector2f(20, thickness),
                                  sf::Vector2f(20, 600));
  levels[numLevels - 1].newSpring(sf::Vector2f(400, 10),
                                  sf::Vector2f(140, 800));

  for (int i = 400; i < 1600; i += 300) {
    levels[numLevels - 1].newEnemy(sf::Vector2f(i, i));
  }

  for (int i = 100; i < 200; i += 200) {
    levels[numLevels - 1].newCoin(sf::Vector2f(i, 500));
  }
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

      gameLoop();

      // game complete
      time = clock.getElapsedTime();
      gameTime = time.asSeconds();
      highscores.write(gameTime);

      menu.displayWinScreen(&win, gameTime, highscores.highscore);

      highscores.read();  // update highscore

    } else {
      menu.displayLeaderBoard(&win, highscores.highscore);
    }
  }
}