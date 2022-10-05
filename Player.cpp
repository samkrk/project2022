#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

Player::Player(sf::Vector2f size){
    player.setSize(size);
    player.setFillColor(sf::Color::Green);
}

void Player::drawTo(sf::RenderWindow &window){
    window.draw(player);
}

void Player::move(sf::Vector2f distance){
    player.move(distance);
}

void Player::setPos(sf::Vector2f newPos){
    player.setPosition(newPos);
}

float Player::getX(){
    return player.getPosition().x;
}

float Player::getY(){
    return player.getPosition().y;
}