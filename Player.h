#pragma once

class Player {
public:
    Player(int startX, int startY, int startFuel, int startHealth);

    void moveTo(int newX, int newY);
    int getX() const;
    int getY() const;

    int getFuel() const;
    void changeFuel(int newFuel);

    int getHealth() const;
    void changeHealth(int newHealth);

    bool isDead() const;
    bool isOutOfFuel() const;

private:
    int x;
    int y;
    int fuel;
    int health;
};
