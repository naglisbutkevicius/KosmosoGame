#include "MapCreator.h"
#include <iostream>

MapCreator::MapCreator(int w, int h, char wall, char floor)
    : width(w),
      height(h),
      wallChar(wall),
      floorChar(floor),
      player({-1,-1}),
      dest({-1,-1})
{
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive integers.");
    }
    generateBaseMap();
    updateMapRepresentation();
}

bool MapCreator::placePlanet(int x, int y) {
    if (!inBounds(x, y) || isWall(x, y)) return false;
    if (!contains(planets, {x,y})) planets.push_back({x,y});
    updateMapRepresentation();
    return true;
}

/*
bool MapCreator::removePlanet(int x, int y) {
    for (auto it = planets.begin(); it != planets.end(); ++it) {
        if (*it == std::pair<int,int>{x,y}) {
            planets.erase(it);
            updateMapRepresentation();
            return true;
        }
    }
    return false;
}*/

bool MapCreator::setDestination(int x, int y) {
    if (!inBounds(x, y) || isWall(x, y)) return false;
    dest = {x,y};
    updateMapRepresentation();
    return true;
}

/*
void MapCreator::clearDestination() {
    dest = {-1,-1};
    updateMapRepresentation();
}*/

bool MapCreator::setPlayer(int x, int y) {
    if (!inBounds(x, y) || isWall(x, y)) return false;
    player = {x,y};
    updateMapRepresentation();
    return true;
}

bool MapCreator::movePlayerTo(int x, int y) {
    if (!inBounds(x, y) || isWall(x, y)) return false;
    player = {x,y};
    updateMapRepresentation();
    return true;
}

/*
bool MapCreator::setObject(int x, int y, char objChar) {
    if (!inBounds(x, y) || isWall(x, y)) return false;
    if (objChar == '@' || objChar == 'O' || objChar == '*') return false;
    map[y][x] = objChar;
    updateMapRepresentation();
    return true;
}*/

char MapCreator::getTile(int x, int y) const {
    if (!inBounds(x,y)) {
        throw std::out_of_range("Coordinates out of bounds");
    }
    return map[y][x];
}

void MapCreator::print() const {
    for (const auto& row : map) {
        std::cout << row << '\n';
    }
}

void MapCreator::generateBaseMap() {
    baseMap.clear();
    baseMap.reserve(height);

    for (int y = 0; y < height; ++y) {
        std::string row;
        row.reserve(width);

        for (int x = 0; x < width; ++x) {
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                row += wallChar;
            else
                row += floorChar;
        }
        baseMap.push_back(row);
    }
}

void MapCreator::updateMapRepresentation() {
    map = baseMap;

    for (const auto& p : planets) {
        if (inBounds(p.first, p.second) && !isWall(p.first, p.second))
            map[p.second][p.first] = '@';
    }

    if (inBounds(dest.first, dest.second) && !isWall(dest.first, dest.second))
        map[dest.second][dest.first] = 'O';

    if (inBounds(player.first, player.second) && !isWall(player.first, player.second))
        map[player.second][player.first] = '*';
}

bool MapCreator::inBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

bool MapCreator::isWall(int x, int y) const {
    return baseMap[y][x] == wallChar;
}

bool MapCreator::contains(const std::vector<std::pair<int,int>>& v,
    std::pair<int,int> p) {
    for (const auto& item : v) {
        if (item == p) return true;
    }
    return false;
}
