#include "Player.h"

Player::Player(int startX, int startY, int startFuel, int startHealth)
    : x(startX),
      y(startY),
      fuel(startFuel),
      health(startHealth) {}

void Player::moveTo(int newX, int newY) {
    x = newX;
    y = newY;
}

int Player::getX() const {
    return x;
}

int Player::getY() const {
    return y;
}

int Player::getFuel() const {
    return fuel;
}

void Player::changeFuel(int newFuel) {
    fuel += newFuel;
    if (fuel < 0) fuel = 0;
}

int Player::getHealth() const {
    return health;
}

void Player::changeHealth(int newHealth) {
    health += newHealth;
    if (health < 0) health = 0;
}

bool Player::isDead() const {
    return health <= 0;
}

bool Player::isOutOfFuel() const {
    return fuel <= 0;
}
