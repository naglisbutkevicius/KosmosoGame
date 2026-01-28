#include "Planet.h"

Planet::Planet(int x, int y, const std::string& name)
    : x(x), y(y), name(name) {}

int Planet::getX() const {
    return x;
}

int Planet::getY() const {
    return y;
}

const std::string& Planet::getName() const {
    return name;
}
