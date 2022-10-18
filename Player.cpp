#include "Player.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Player::Player() {
  size = sf::Vector2f(50, 50);
  body.setSize(size);
  fillColor = sf::Color(222, 48, 34);
  body.setFillColor(fillColor);
  body.setOutlineColor(sf::Color::White);
  body.setOutlineThickness(2.f);

  this->magSize = 5;
  this->bulletIndex = 0;
  bullets = new Bullet[magSize];

  time.asMilliseconds();
  this->fireRate = 300;
  this->relaodTime = 1000;

  this->reloading = false;

  /*if (!skin.loadFromFile("coin.jpeg")){
    std::cout<< "FAILED" << std::endl;
  }
  body.setTexture(&skin);
  */
}

void Player::shoot(int direction) {
  if (bulletIndex == magSize) {
    return;
  }
  bullets[bulletIndex].setPos(this->position + 0.5f * this->size);
  bullets[bulletIndex].setVel(sf::Vector2f(bullets->speed * direction, 0));
  bulletIndex++;
  clock.restart();
}

void Player::reload() {
  reloading = true;
  if (timeSinceShot > relaodTime) {
    reloading = false;
    bulletIndex = 0;
    for (int i = 0; i < magSize; i++) {
      bullets[i].setVel(zeroVec);
      bullets[i].setPos(ofScreenPos);
    }
  }
}

void Player::isKilled(Entity *enemy) {
  if (collision(enemy)) {
    this->isAlive = false;
    this->position = sf::Vector2f(200, 200);
    update();
  }
}

void Player::respawn(sf::Vector2f spawnCoords) {
  this->isAlive = true;
  this->bulletIndex = 0;
  bullets = new Bullet[magSize];
  velocity = zeroVec;
  acceleration = zeroVec;
  position = spawnCoords;
}

void Player::print() {
  std::cout << "Player which the user controls" << std::endl;
}