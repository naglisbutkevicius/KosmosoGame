#pragma once

#include <vector>
#include <string>

#include "MapCreator.h"
#include "Player.h"
#include "Planet.h"
#include "Path.h"
#include "Risk.h"

class GameInterface {
public:
    GameInterface(int mapWidth, int mapHeight, char wallChar, char floorChar,
                  int playerX, int playerY, int playerFuel, int playerHealth,
                  int destX, int destY);

    void addPlanet(int x, int y, const std::string& name);
    void addPath(int x1, int y1, int x2, int y2, int fuelRequired, int riskLevel);

    void printMap() const;


    int getPlayerX() const;
    int getPlayerY() const;
    int getPlayerFuel() const;
    int getPlayerHealth() const;

    bool isPlayerDead() const;
    bool isPlayerOutOfFuel() const;
    bool isPlayerStuck() const;


    struct AvailablePath {
        int index;
        int toX;
        int toY;
        int fuelRequired;
        int riskLevel;
        std::string destinationName;
    };

    std::vector<AvailablePath> getAvailablePaths() const;

    bool hasWon() const;

    struct MoveResult {
    bool moved = false;
    bool win = false;
    bool dead = false;
    bool outOfFuel = false;
    RiskResult encounter;
    std::string message;
};

    MoveResult attemptMove(int availablePathIndex);

private:
    const Planet* findPlanetAt(int x, int y) const;

    bool isValidChoiceIndex(int idx, int size) const;
    bool hasEnoughFuel(const Path& path) const;

    void payFuel(const Path& path);
    void movePlayerTo(int x, int y);

    void updateEndState(MoveResult& result) const;
    void applyEncounterMessage(MoveResult& result) const;

private:
    int destX;
    int destY;
    MapCreator map;
    Player player;
    std::vector<Planet> planets;
    std::vector<Path> paths;
};
