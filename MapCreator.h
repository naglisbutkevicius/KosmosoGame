#pragma once

#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

class MapCreator {
public:
    MapCreator(int w, int h, char wall = '#', char floor = '.');

    bool placePlanet(int x, int y);
    bool removePlanet(int x, int y);

    bool setDestination(int x, int y);
    void clearDestination();

    bool setPlayer(int x, int y);
    bool movePlayerTo(int x, int y);

    bool setObject(int x, int y, char objChar);

    char getTile(int x, int y) const;

    void print() const;

private:
    int width;
    int height;
    char wallChar;
    char floorChar;

    std::vector<std::string> baseMap;
    std::vector<std::string> map;

    std::pair<int,int> player;
    std::pair<int,int> dest;
    std::vector<std::pair<int,int>> planets;

private:
    void generateBaseMap();
    void updateMapRepresentation();

    bool inBounds(int x, int y) const;
    bool isWall(int x, int y) const;

    static bool contains(const std::vector<std::pair<int,int>>& v, std::pair<int,int> p);
};
