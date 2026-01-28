#pragma once

#include <string>

class Planet {
public:
    Planet(int x, int y, const std::string& name);

    int getX() const;
    int getY() const;
    const std::string& getName() const;

private:
    int x;
    int y;
    std::string name;
};
