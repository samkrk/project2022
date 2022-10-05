#include "Game.h"

#include <iostream>

#include "Entity.h"
#include "Player.h"
using namespace std;

Game::Game() {
  this->gameName = "Platform Game";
  this->gameSpeed = 0.05;
  this->drag = 0.0;
  this->damping = 0.5;
  this->gravity = 1;

  win.create(sf::VideoMode(1200,800), gameName);
}

void Game::readInputs(Player *player) {
  player->setAcc(sf::Vector2f(0, gravity));
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
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
}

void Game::calcPosition(Entity *entity) {
  entity->addAcc(-entity->velocity * this->drag);  // friction F = kv, therefore a = kv
  entity->addVel(entity->acceleration * this->gameSpeed);
  entity->addPos(entity->velocity * this->gameSpeed);
  entity->update();
}

void Game::collision(Entity *entity) {
  if (entity->position.y > win.getSize().y - entity->size.y)
  {
    entity->setVel(damping*sf::Vector2f(entity->velocity.x,-entity->velocity.y));
    entity->setPos(
        sf::Vector2f(entity->position.x, win.getSize().y - entity->size.y));
  }
  if (entity->position.y < 0) {
    entity->setVel(damping *
                   sf::Vector2f(entity->velocity.x, -entity->velocity.y));
    entity->setPos(sf::Vector2f(entity->position.x, 0));
  }
  if (entity->position.x > win.getSize().x - entity->size.x) {
    entity->setVel(damping *
                   sf::Vector2f(-entity->velocity.x, entity->velocity.y));
    entity->setPos(
        sf::Vector2f(win.getSize().x - entity->size.x, entity->position.y));
  }
  if (entity->position.x < 0) {
    entity->setVel(damping *
                   sf::Vector2f(-entity->velocity.x, entity->velocity.y));
    entity->setPos(sf::Vector2f(0, entity->position.y));
  }
}

void Game::run() {
  while (win.isOpen()) {

    sf::Event event;
    while (win.pollEvent(event)) {
      if (event.type == sf::Event::Closed) win.close();
    }

    readInputs(&player);

    collision(&player);

    calcPosition(&player);

    cout << "Pos: " << player.position.x << " , " << player.position.y;
    cout << " Vel: " << player.velocity.x << " , " << player.velocity.y;
    cout << " Acc: " << player.acceleration.x << " , " << player.acceleration.y << endl;

    this->win.clear();
    win.draw(player.body);
    this->win.display();
  }
}