#include "Game.h"

#include <math.h>

#include <iostream>

#include "Entity.h"
#include "Player.h"
using namespace std;

Game::Game() {
  this->gameName = "Platform Game";
  this->gameSpeed = 0.02;
  this->drag = 0.0001;  // force oposing velocity
  this->damping = 0.3;  // loss in energy bouncing off walls
  this->gravity = 2.2;
  this->jumpPower = 60;
  this->jumpPowerHoz = 20;

  win.create(sf::VideoMode(1800, 1500), gameName);
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
    std::cout << (1000-player->timeSinceShot)/1000 << "sec remaining" << std::endl;
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

void Game::collision(Entity *entity) {
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

void Game::run() {
  // game loop
  while (win.isOpen()) {
    sf::Event event;
    while (win.pollEvent(event)) {
      if (event.type == sf::Event::Closed) win.close();
    }

    // update player

    collision(&player);

    readInputs(&player);

    calcPositionDrag(&player);

    // update bullets

    for (int i = 0; i < player.magSize; i++) {
      calcPosition(&player.bullets[i]);
    }

    // display objects to screen

    this->win.clear();

    win.draw(player.body);

    for (int i = 0; i < player.magSize; i++) {
      win.draw(player.bullets[i].body);
    }

    this->win.display();
  }
}